#include <stdio.h>
#include "math.h"
#include "common.h"

// REMOVE ASAP
#include "map.h"

#include "geometry.h"


void buildVertexTree(t_geometry* geometry) {
	
	int i, j, k, l;
	t_face* face = geometry->faces;
	t_vertex* vertex;
	
	for ( i = 0; i < geometry->nb_faces; i ++ ) {
		
		vertex = face->vertices;
		
		for ( j = 0; j < face->nb_vertices; j ++ ) {
			
			vertices = findVertex(geometry, vertex, face);
			
			vertex = vertex->next;
		}
		
		face = face->next;
	}
	
}

t_vertices findVertex(t_geometry* geometry, t_vertex* vertex, t_face* parent) {
	t_face* face = geometry->faces;
	t_vertex* v;
	t_vertices vertices;
	t_list_vertex *vert;
	for ( i = 0; i < geometry->nb_faces; i ++ ) {
		if ( face == parent ) continue;
		v = face->vertices;
		for( j = 0; j < face->nb_vertices; j ++ ) {
			if (v.x == vertex.x &&
				v.y == vertex.y &&
				v.z == vertex.z )
			{	
				if( (vert = (t_list_vertex*)malloc(sizeof(t_list_vertex))) == NULL) {
					printf("Error while trying to allocate %d bytes to memory! In %s at line %s", sizeof(t_face) * datac, __FILE__, __LINE__);
					return NULL;
				}
				
				if ( vertices.nb_vertices > 0 ) {
					vertices.tail->next = vert;
					vert->prev = vertices.tail;
					vert->next = vertices.head;
					vertices->head->prev = vert;
					vertices->tail = vert;
				} else {
					vertices.head = vert;
					vertices.tail = vert;
				}
				
				vertices.nb_vertices++;
			}
		}
	}
	
	return vertices;
}








