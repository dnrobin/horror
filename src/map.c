#include "shared.h"
#include "map.h"

#include "res.h"
#include "graphics.h"
#include "math.h"
#include "game.h"
#include "collision.h"

#include "parson.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

#include "glad.h"

int loadMapJSON(const char* filename) {
	JSON_Value* JSON;
	char filepath[256];
	
	// get full include path to file
	strcpy(filepath, env_base_path);
	strcat(filepath, filename);
	
	#ifdef __DEBUG
		printf("-- loading map from file %s\n",filepath);
	#endif
	
	// open the file for reading
	if( (JSON = json_parse_file(filepath)) == NULL ) {
		printf(KRED "Error: file not found \"%s\"\n" KNRM,filepath);
		return 0;
	}

	// step into main object scope
	JSON = json_value_get_object(JSON);

	// get faces array
	JSON_Array* faces;
	if( (faces = json_object_get_array(json_object_get_object(JSON, "geometry"), "faces")) == NULL ) {
		printf(KRED "Error: geometry information missing\n" KNRM);
		return 0;
	}
	
	#ifdef __DEBUG
		printf("-- building geometry\n");
	#endif
	
	// build geometry into display list
	glNewList(GL_LIST_ID_MAP, GL_COMPILE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	for ( int f = 0; f < json_array_get_count(faces); f ++ ) {
		JSON_Object* face = json_array_get_object(faces, f);
		JSON_Array* vertices = json_object_get_array(face, "vertices");
		JSON_Array* normal = json_object_get_array(face, "normal");
		int nverts = json_array_get_count(vertices);
		
		// set the face texture id
		glBindTexture(GL_TEXTURE_2D, 0);

		// set the face normal
		glNormal3f(
			json_array_get_number(normal, 0),
			json_array_get_number(normal, 1),
			json_array_get_number(normal, 2)
			);

		// draw face
		if ( nverts == 4 ) {
			glBegin(GL_QUADS);
		} else {
			glBegin(GL_TRIANGLES);
		}
			for ( int v = 0; v < nverts; v ++ ) {
				JSON_Object* vertex = json_array_get_object(vertices, v);
				JSON_Array* color = json_object_get_array(vertex, "color");
				JSON_Array* texcoords = json_object_get_array(vertex, "texcoords");
				JSON_Array* position = json_object_get_array(vertex, "position");
				glColor4f(
					json_array_get_number(color, 0),
					json_array_get_number(color, 1),
					json_array_get_number(color, 2),
					json_array_get_number(color, 3)
					);
				glTexCoord2f(
					json_array_get_number(texcoords, 0),
					json_array_get_number(texcoords, 1)
					);
				glVertex3f(
					json_array_get_number(position,0),
					json_array_get_number(position,1),
					json_array_get_number(position,2)
					);
			}
			glEnd();
	}
	
	glEndList();

	// build wireframe view
	glNewList(GL_LIST_ID_WIREFRAME, GL_COMPILE);

	json_value_free(JSON);
	glColorMaterial(GL_FRONT_AND_BACK, 0);

	for ( int f = 0; f < json_array_get_count(faces); f ++ ) {
		JSON_Object* face = json_array_get_object(faces, f);
		JSON_Array* vertices = json_object_get_array(face, "vertices");
		JSON_Array* normal = json_object_get_array(face, "normal");
		int nverts = json_array_get_count(vertices);

		glColor4f(1.0, 1.0, 1.0, 1.0);

		// draw lines
			for ( int v = 0; v < nverts; v ++ ) {
				JSON_Array* p1 = json_object_get_array(json_array_get_object(vertices, v), "position");
				JSON_Array* p2 = json_object_get_array(json_array_get_object(vertices, (v+1>=nverts?0:v+1)), "position");
				glBegin(GL_LINES);
				glVertex3f( json_array_get_number(p1,0), json_array_get_number(p1,1), json_array_get_number(p1,2) );
				glVertex3f( json_array_get_number(p2,0), json_array_get_number(p2,1), json_array_get_number(p2,2) );
				glEnd();
			}
			
	}
	
	glEndList();

	return 1;
}

int saveMap(const int mapc, const float* mapv, const char* filename ) {
	
	FILE* fp;
	t_map_descriptor mapdesc;
	t__face* faces;
	int count = (int)(mapc / 3 / 6);
	
	// allocate buffer memory
	if( (faces = (t__face*)malloc(sizeof(t__face)*count)) == NULL ) {
		printf("Error: could not allocate memory for map!\n");
		return 0;
	}
	
	// compile faces to memory
	int i, a;
	for( i = 0; i < count; i ++ ) {
		faces[i].type = FACE_TYPE_4;
		for(a=0;a<4;a++) {
			faces[i].verts[a].x = mapv[i*18+a*3+0];
			faces[i].verts[a].y = mapv[i*18+a*3+1];
			faces[i].verts[a].z = mapv[i*18+a*3+2];
			faces[i].colors[a].r = mapv[i*18+4*3+0];
			faces[i].colors[a].g = mapv[i*18+4*3+1];
			faces[i].colors[a].b = mapv[i*18+4*3+2];
			faces[i].colors[a].a = 	1.0;
		}
		
		faces[i].tcoords[0].x = 0.0;
		faces[i].tcoords[0].y = 0.0;
		faces[i].tcoords[1].x = 1.0;
		faces[i].tcoords[1].y = 0.0;
		faces[i].tcoords[2].x = 1.0;
		faces[i].tcoords[2].y = 1.0;
		faces[i].tcoords[3].x = 0.0;
		faces[i].tcoords[3].y = 1.0;
		
		faces[i].normal.x = mapv[i*18+5*3+0];
		faces[i].normal.y = mapv[i*18+5*3+1];
		faces[i].normal.z = mapv[i*18+5*3+2];
		
		if ( mapv[i*18+5*3+1] == 0.0 ) {
			faces[i].texid = 987;
		} else if ( mapv[i*18+5*3+1] == 1.0 ) {
			faces[i].texid = 988;
		} else {
			faces[i].texid = 989;
		}
	}
	
	// open file for writing
	if( (fp=fopen(filename, "w")) == NULL ) {
		printf("Error: could not open file for output!\n");
		return 0;
	}
	
	// set number of faces
	mapdesc.nb_faces = count;
	
	// write map descriptor to file
	if( fwrite(&mapdesc, sizeof(mapdesc), 1, fp) != 1 ) {
		printf("Error: could not write descriptor to output file!\n");
		return 0;
	}
	
	// write faces to file
	for ( i = 0; i < count; i ++ ) {
		if( fwrite(&faces[i], sizeof(t__face), 1, fp) != 1 ) {
			printf("Error: could not write data to output file!\n");
			return 0;
		}
	}
	
	free(faces);
	fclose(fp);
	
	return 1;
}

int loadMap(const char* filename) {
	
	FILE* fp;
	char filepath[256];
	t_map_descriptor map;
	t__face* data;
	
	// get full include path to file
	strcpy(filepath, env_base_path);
	strcat(filepath, filename);
	
	#ifdef __DEBUG
		printf("-- loading map from file %s\n",filepath);
	#endif
	
	// open the file for reading
	if( (fp = fopen(filepath, "rb")) == NULL ) {
		printf("Error: file not found \"%s\"\n",filepath);
		return 0;
	}
	
	// read map descriptor
	if( fread(&map, sizeof(t_map_descriptor), 1, fp) != 1 ) {
		printf("Error: map file corrupted!\n");
		return 0;
	}
	
	// allocate memory for geometry
	if( (data = (t__face*)malloc(sizeof(t__face) * map.nb_faces)) == NULL) {
		printf("Error: failed allocating memory for map!\n");
		return 0;
	}
	
	// read map gemoetry
	int i, j, k;
	for( i = 0; i < map.nb_faces; i ++ ) {
		if( fread(&data[i], sizeof(t__face), 1, fp) != 1 ) {
			printf("Error: map file corrupted! \n");
			return 0;
		}
	}
	
	// close file
	fclose(fp);
	
	// set memory for collisions
	g_collisions_count = map.nb_faces;
	if( (g_collisions = (h_collision_surface)malloc(sizeof(t_collision_surface) * g_collisions_count)) == NULL ) {
		printf("Error: failed to set memory for collisions!\n");
		return 0;
	}
	
	#ifdef __DEBUG
		printf("-- building geometry\n");
	#endif
	
	t__face* face;
	h_texture_resource_descriptor tex;
	
	glNewList(GL_LIST_ID_MAP, GL_COMPILE);
	
	glEnable( GL_COLOR_MATERIAL );
	//glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	GLfloat defaultAmbient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat defaultDiffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat defaultSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat defaultShininess = 1.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, defaultAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, defaultDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, defaultShininess);
	
	for ( i = 0; i < map.nb_faces; i ++ ) {
		face = &data[i];
		
		/*
		printf("\nFACE(%d) - type : %d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",i,face->type);
		printf("Vertex 1 : {%0.1f, %0.1f, %0.1f}\n",face->verts[0].x, face->verts[0].y, face->verts[0].z);
		printf("Vertex 2 : {%0.1f, %0.1f, %0.1f}\n",face->verts[1].x, face->verts[1].y, face->verts[1].z);
		printf("Vertex 3 : {%0.1f, %0.1f, %0.1f}\n",face->verts[2].x, face->verts[2].y, face->verts[2].z);
		printf("Vertex 4 : {%0.1f, %0.1f, %0.1f}\n",face->verts[3].x, face->verts[3].y, face->verts[3].z);
		printf("TexCoord 1 : {%0.1f, %0.1f}\n",face->tcoords[0].x, face->tcoords[0].y);
		printf("TexCoord 2 : {%0.1f, %0.1f}\n",face->tcoords[1].x, face->tcoords[1].y);
		printf("TexCoord 3 : {%0.1f, %0.1f}\n",face->tcoords[2].x, face->tcoords[2].y);
		printf("TexCoord 4 : {%0.1f, %0.1f}\n",face->tcoords[3].x, face->tcoords[3].y);
		printf("Color 1 : {%0.1f, %0.1f, %0.1f}\n",face->colors[0].r, face->colors[0].g, face->colors[0].b);
		printf("Color 2 : {%0.1f, %0.1f, %0.1f}\n",face->colors[1].r, face->colors[1].g, face->colors[1].b);
		printf("Color 3 : {%0.1f, %0.1f, %0.1f}\n",face->colors[2].r, face->colors[2].g, face->colors[2].b);
		printf("Color 4 : {%0.1f, %0.1f, %0.1f}\n",face->colors[3].r, face->colors[3].g, face->colors[3].b);
		printf("Normal : {%0.1f, %0.1f, %0.1f}\n",face->normal.x, face->normal.y, face->normal.z);
		printf("TexId : %d\n",face->texid);
		*/
		
		// set collision surfaces
		g_collisions[i].v1 = (t_vec3){ face->verts[0].x, (face->normal.y==1.0?-0.35:face->verts[0].y), face->verts[0].z };
		g_collisions[i].v2 = (t_vec3){ face->verts[1].x, (face->normal.y==1.0?-0.35:face->verts[1].y), face->verts[1].z };
		g_collisions[i].v3 = (t_vec3){ face->verts[2].x, (face->normal.y==1.0?-0.35:face->verts[2].y), face->verts[2].z };
		g_collisions[i].v4 = (t_vec3){ face->verts[3].x, (face->normal.y==1.0?-0.35:face->verts[3].y), face->verts[3].z };
		g_collisions[i].normal = (t_vec3){ face->normal.x, face->normal.y, face->normal.z };
		
		// draw subdivision surfaces for better lighting
		glBindTexture(GL_TEXTURE_2D, g_textures[face->texid]);
		glLineWidth(5);
		
		subdivision4(
			convertFace4(face), 		// face pointer
			0, 							// group u texcoord
			0, 							// group v texcoord
			4,							// number of divisions per axis
			2);							// number of recursions

			// glColor3f(1.0, 1.0, 1.0);
			// glBegin(GL_LINES);
			// for ( j = 0; j < 4; j ++ ) {
			// 	glVertex3f(face->verts[j].x, face->verts[j].y, face->verts[j].z);
			// 	glVertex3f(face->verts[j].x + 0.2*face->normal.x, face->verts[j].y + 0.2*face->normal.y, face->verts[j].z + 0.2*face->normal.z);
			// }
			// glEnd();
	}
	
	glEndList();
	
	return 1;
}

void subdivision4(const t_face4* face, const int _u, const int _v, const int ndivs, int rec) {
	
	int i, j;
	
	t_vec3 v1 = face->vertices[0];
	t_vec3 v2 = face->vertices[1];
	t_vec3 v3 = face->vertices[2];
	t_vec3 v4 = face->vertices[3];
	
	// calculate new face vertices
	t_vec3 v[] = {
		add( scale( sub( v2, v1 ), 0.5 ), v1 ),	// v[0]
		add( scale( sub( v3, v2 ), 0.5 ), v2 ),	// v[1]
		add( scale( sub( v4, v3 ), 0.5 ), v3 ),	// v[2]
		add( scale( sub( v1, v4 ), 0.5 ), v4 ),	// v[3]
		add( scale( sub( v3, v1 ), 0.5 ), v1 )		// v[4]
	};
	
	// create new faces
	int ru = _u*(int)pow(2, (rec+1))/ndivs, rv = _v*(int)pow(2, (rec+1))/ndivs;
	t_face4 faces[4];
	faces[0] = *face;
	faces[0].vertices[0] = v1;
	faces[0].vertices[1] = v[0];
	faces[0].vertices[2] = v[4];
	faces[0].vertices[3] = v[3];
	faces[0].texcoords[0].x += ru; faces[0].texcoords[0].y += rv;
	faces[0].texcoords[1].x += ru; faces[0].texcoords[1].y += rv;
	faces[0].texcoords[2].x += ru; faces[0].texcoords[2].y += rv;
	faces[0].texcoords[3].x += ru; faces[0].texcoords[3].y += rv;

	faces[1] = *face;
	faces[1].vertices[0] = v[0];
	faces[1].vertices[1] = v2;
	faces[1].vertices[2] = v[1];
	faces[1].vertices[3] = v[4];
	faces[1].texcoords[0].x += 1 + ru; faces[1].texcoords[0].y += rv;
	faces[1].texcoords[1].x += 1 + ru; faces[1].texcoords[1].y += rv;
	faces[1].texcoords[2].x += 1 + ru; faces[1].texcoords[2].y += rv;
	faces[1].texcoords[3].x += 1 + ru; faces[1].texcoords[3].y += rv;

	faces[2] = *face;
	faces[2].vertices[0] = v[4];
	faces[2].vertices[1] = v[1];
	faces[2].vertices[2] = v3;
	faces[2].vertices[3] = v[2];
	faces[2].texcoords[0].x += 1 + ru; faces[2].texcoords[0].y += 1 + rv;
	faces[2].texcoords[1].x += 1 + ru; faces[2].texcoords[1].y += 1 + rv;
	faces[2].texcoords[2].x += 1 + ru; faces[2].texcoords[2].y += 1 + rv;
	faces[2].texcoords[3].x += 1 + ru; faces[2].texcoords[3].y += 1 + rv;

	faces[3] = *face;
	faces[3].vertices[0] = v[3];
	faces[3].vertices[1] = v[4];
	faces[3].vertices[2] = v[2];
	faces[3].vertices[3] = v4;
	faces[3].texcoords[0].x += ru; faces[3].texcoords[0].y += 1 + rv;
	faces[3].texcoords[1].x += ru; faces[3].texcoords[1].y += 1 + rv;
	faces[3].texcoords[2].x += ru; faces[3].texcoords[2].y += 1 + rv;
	faces[3].texcoords[3].x += ru; faces[3].texcoords[3].y += 1 + rv;

	if ( rec > 1 ) {
		--rec;
		subdivision4(&faces[0], 0, 0, ndivs, rec);
		subdivision4(&faces[1], 1, 0, ndivs, rec);
		subdivision4(&faces[2], 1, 1, ndivs, rec);
		subdivision4(&faces[3], 0, 1, ndivs, rec);
	} else {

		float WALL_HEIGHT_OFFSET = 0.2;

		for ( i = 0; i < 4; i ++ ) {
			
			glNormal3f(faces[i].normal.x, faces[i].normal.y, faces[i].normal.z);

			glBegin(GL_QUADS);
			for ( j = 0; j < 4; j ++ ) {
				float MESSED_UP_CEILING_OFFSET = (rand()%100)*0.0008 * 1;
				glColor4f(faces[i].colors[j].r,faces[i].colors[j].r,faces[i].colors[j].r, 1.0);
				glTexCoord2f(faces[i].texcoords[j].x / ndivs, faces[i].texcoords[j].y / ndivs);
				glVertex3f(faces[i].vertices[j].x, faces[i].vertices[j].y + (faces[i].vertices[j].y>0.4?(WALL_HEIGHT_OFFSET+MESSED_UP_CEILING_OFFSET):0), faces[i].vertices[j].z);
			}
			glEnd();

		}
	}
	
}

t_face4* convertFace4( const t__face* f ) {
	int i;
	t_face4* face;
	face = malloc(sizeof(t_face4));
	
	for(i=0; i<4; i++) {
	face->vertices[i] = f->verts[i];
	face->texcoords[i] = f->tcoords[i];
	face->colors[i] = f->colors[i];
	}
	face->normal = f->normal;
	
	return face;
}