#include <stdlib.h>
#include <stdio.h>

#include "mem.h"
#include "math.h"
#include "geometry.h"

#include "map.h"

int rewriteMap(const char* filepath) {
	
	FILE* fp;
	t_map_descriptor map;
	t__face* data;
	
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
	
	// build geometry 
	t_geometry geometry;
	buildGeometryList(&geometry, map.nb_faces, data);

	h_array shared_vertices;
	t_face* face, adjacent_face;
	t_vertex* vertex;
	
	// optimize geometry by merging coplanar faces
	/*
	array_set_internal_position(&geometry.faces, 0);
	for ( i = 0; i < geometry.faces.count; i ++ ) {
		
		face = array_next(&geometry.faces);
		
		array_set_internal_position(&face->vertices, 0);
		for ( j = 0; j < face->vertices.count; j ++ ) {
			
			vertex = array_next(&face->vertices);
			
			array_set_internal_position(&vertex->faces, 0);
			for ( k = 0; k < vertex->faces.count; k ++ ) {
				
				adjacent_face = array_next(&vertex->faces);
				
				if ( adjacent_face == face ) continue;
				
				if ( vcmpr(&adjacent_face->normal, &face->normal) != 0 ) {
					
					// coplanar, check shared vertices
					shared_vertices = shared_vertices(adjacent_face, face);
					
					if ( shared_vertices.count > 1 ) {
						get_array(shared_vertices, 0);
						
						adjacent_face
					}
				}
				
			}
			
		}
		
	}
	*/
	
	// save back to file
	if( (fp = fopen(filepath, "w")) == NULL ) {
		printf("Error: file not found \"%s\"\n",filepath);
		return 0;
	}
	
}

h_array shared_vertices(t_face* face1, t_face* face2) {
	int i, j;
	t_vertex* v1, v2;
	h_array array = array();
	array_set_internal_position(&face1->vertices, 0);
	for( i = 0; i < face1->vertices.count; i++ ) {
		v1 = array_next(&face1->vertices)
		array_set_internal_position(&face2->vertices, 0);
		for( j = 0; j < face2->vertices.count; j++ ) {
			v2 = array_next(&face2->vertices);
			if( v1 == v2 )
				array_push(array, v1);
		}
	}
	return array;
}

void buildGeometryList(h_geometry geometry, int datac, t__face* datav) {
	
	int i, j, k;
	t_face* faces;
	t_face_list_item* face_list_items;
	t_vertex* vertex;
	t_vertex_list_item* vertex_list_items;
	
	// create faces list
	if( (geometry->faces = (h_face_list)malloc(sizeof(t_face_list))) == NULL ) {
		printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_face_list), __FILE__, __LINE__);
		return;
	}
	
	// set number of faces
	geometry->nb_faces = datac;
	geometry->faces->nb_items = datac;
	
	// allocate contigeous memory block for faces
	if ( (faces = (t_face*)malloc(sizeof(t_face) * datac)) == NULL ) {
		printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_face) * datac, __FILE__, __LINE__);
		return;
	}
	
	// allocate contigeous memory block for face list items
	if ( (face_list_items = (h_face_list_item)malloc(sizeof(t_face_list_item) * datac)) == NULL ) {
		printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_face_list_item) * datac, __FILE__, __LINE__);
		return;
	}
	
	// set list pointers
	geometry->faces->head = face_list_items;
	geometry->faces->tail = face_list_items;
	geometry->faces->cur = face_list_items;
	
	// iterate through faces data
	for ( i = 0; i < datac; i ++ ) {
		
		// add face list item to list
		if ( i > 0 ) {
			geometry->faces->tail->next = &face_list_items[i];			// link last item's next pointer to new item
			face_list_items[i]->prev = geometry->faces->tail;			// link new item's prev pointer to last item
			geometry->faces->tail = geometry->faces->tail->next;		// set last item to new item
			geometry->faces->tail->next = geometry->faces->head;		// set last item's next pointer to the first
			geometry->faces->head->prev = geometry->faces->tail;		// set the first's prev pointer to the last
		}
		
		// link face list item to actual face
		face_list_items[i]->face = &faces[i];
		
		// set the face values
		faces[i]->options = SURFACE_IS_COLLISION & (faces[i]->normal.y == 1.0 ? SURFACE_IS_FLOOR : 0);
		faces[i]->group = (unsigned char)floor(data[i]->colors[0]*256);	// take red value as group number
		faces[i]->normal = datav[i]->normal;
		faces[i]->texture_id = datav[i]->texid;
		
		// set vertex count
		faces[i]->nb_vertices = datav[i]->type;	// 3 or 4
		
		// allocate new vertex list items
		if ( (vertex_list_items = (h_vertex_list_item)malloc(sizeof(t_vertex_list_item)*faces[i]->nb_vertices)) == NULL ) {
			printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_vertex_list_item)*faces[i]->nb_vertices), __FILE__, __LINE__);
			return;
		}
		
		// set list pointers
		if ( geometry->nb_vertices == 0 ) {
			geometry->vertices->head = vertex_list_items;
			geometry->vertices->tail = vertex_list_items;
			geometry->vertices->cur = vertex_list_items;
		}
		
		geometry->nb_vertices += faces[i]->nb_vertices;
		
		// iterate through vertices
		for ( j = 0; j < faces[i]->nb_vertices; j ++ ) {
			
			// add face list item to list
			if ( j > 0 ) {
				geometry->vertices->tail->next = &vertex_list_items[j];			// link last item's next pointer to new item
				vertex_list_items[j]->prev = geometry->vertices->tail;			// link new item's prev pointer to last item
				geometry->vertices->tail = geometry->vertices->tail->next;		// set last item to new item
				geometry->vertices->tail->next = geometry->vertices->head;		// set last item's next pointer to the first
				geometry->vertices->head->prev = geometry->vertices->tail;		// set the first's prev pointer to the last
			}
			
			// go through existing vertices to get pointer or create a new one
			vertex_list_items[j]->vertex = NULL;
			geometry->vertices->cur = geometry->vertices->head;
			for ( k = 0; k < geometry->vertices->nb_vertices; k ++ ) {
				
				if (geometry->vertices->cur->v.x = data[i]->verts[j].x &&
				 	geometry->vertices->cur->v.y = data[i]->verts[j].y &&
					geometry->vertices->cur->v.z = data[i]->verts[j].z)
				{
					vertex_list_items[j]->vertex = geometry->vertices->cur;
					break;
				}
				
				// move next
				geometry->vertices->cur = geometry->vertices->cur->next;
			}
			
			if ( vertex_list_items[j]->vertex == NULL ) {
				// allocate new vertices
				if ( (vertex_list_items[j]->vertex = (t_vertex*)malloc(sizeof(t_vertex))) == NULL ) {
					printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_vertex), __FILE__, __LINE__);
					return;
				}
			}
			
			// set vertex values
			vertex_list_items[j]->vertex->v = data[i]->verts[j];
			vertex_list_items[j]->vertex->color = data[i]->colors[j];
			vertex_list_items[j]->vertex->tcoord = data[i]->tcoords[j];
			vertex_list_items[j]->vertex->faces = &faces[i];		
		}
	}
}


