#include "shared.h"
#include "r_mesh.h"

#include "glad.h"

int r_create_mesh(mesh_t *mesh)
{
    glGenVertexArrays(1, &mesh->gl_handle);
    glBindVertexArray(mesh->gl_handle);

    for (int b = 0; b < mesh->num_buffers; ++b) {

        glGenBuffers(1, &mesh->buffers[b].gl_handle);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[b].gl_handle);
        glBufferData(GL_ARRAY_BUFFER
            , mesh->buffers[b].vertex_size
            , mesh->buffers[b].data
            , GL_STATIC_DRAW);

        vertex_attrib_t *attribs = mesh->buffers[b].attribs;

        for (int i = 0; i < MAX_VERTEX_ATTRIBUTES; ++i) {
            
            if (!attribs[i].has_data) {
                continue;
            }

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i
                , attribs[i].comps
                , attribs[i].type
                , GL_FALSE
                , attribs[i].stride
                , attribs[i].pointer
            );
        }
    }

    if (mesh->size_indices > 0) {
        GLuint element_buffer;
        glGenBuffers(1, &element_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER
            , mesh->size_indices
            , mesh->indices
            , GL_STATIC_DRAW); 
    }

    glBindVertexArray(0);

    return 0;
}

void r_delete_mesh(mesh_t *mesh)
{
    glDeleteVertexArrays(1, &mesh->gl_handle);
    mesh->gl_handle = 0;
    for (int b = 0; b < mesh->num_buffers; ++b) {
        glDeleteBuffers(1, &mesh->buffers[b].gl_handle);
        mesh->buffers[b].gl_handle = 0;
    }
}

void r_draw_mesh(const mesh_t *mesh)
{
    glBindVertexArray(mesh->gl_handle);

    // TODO: shader program, uniforms, texture samplers, etc. 
    // should already be bound prior to call to this call. Mesh
    // material info is stored separately.

    if (mesh->size_indices > 0) {
        glDrawElements(mesh->draw_type
            , mesh->num_indices
            , GL_UNSIGNED_INT
            , 0);
    }
    else {
        glDrawArrays(mesh->draw_type, 0, mesh->num_vertices);
    }

    glBindVertexArray(0);
}