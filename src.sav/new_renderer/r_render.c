#include "shared.h"
#include "r_render.h"
#include "r_mesh.h"
#include "shader.h"

#include "glad.h"

static GLuint framebuffer;
static GLuint tex_attachment0;
static GLuint tex_attachment1;
static GLuint tex_attachment2;
static GLuint tex_depth;

static GLuint debug_gbuffers_shader;

//========================================================================================

static void setup_3d_rendering()
{
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
}

static void setup_2d_rendering()
{
    glDisable(GL_DEPTH);
    glDisable(GL_DEPTH_TEST);
}

// static void setup_render_pass(const render_pass_t *pass)
// {
//     switch (pass->type) {
//         case RENDER_PASS_GEOMETRY:
//             setup_3d_rendering();
//             break;

//         case RENDER_PASS_LIGHTING:
//         case RENDER_PASS_SCREEN_EFFECTS:
//             setup_2d_rendering();
//             break;
//     }
// }

static void setup_rendering(const render_scene_t *scene)
{
    glClearColor(
          scene->fog_color[0]
        , scene->fog_color[1]
        , scene->fog_color[2]
        , scene->fog_color[3]
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL);
    // glStencilFunc()

    // glEnable(GL_SCISSOR_TEST);

    glPolygonMode(GL_FRONT, GL_FILL);
    // glPolygonOffset
    glFrontFace(GL_CCW);

    // wireframe?
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void geometry_pass(const render_scene_t *scene)
{
    for (int i = 0; i < scene->num_meshes; ++i) {

        render_mesh_t *mesh = &scene->meshes[i];

        // TODO: frustum cull here

        glUseProgram(mesh->mesh->material.program_handle);

        // Set material
        // glBindTexture(GL_TEXTURE0 + MATERIAL_BASE_COLOR_MAP, mat->base_color);
        // glBindTexture(GL_TEXTURE0 + MATERIAL_BASE_COLOR_MAP, mat->base_color);
        
        r_draw_mesh(mesh->mesh);

        glUseProgram(0);
    }
}

static void light_pass(const render_scene_t *scene)
{
    // TODO::::
    int light_shader = 0;
    glUseProgram(light_shader);

    for (int i = 0; i < scene->num_meshes; ++i) {

        render_mesh_t *mesh = &scene->meshes[i];

        // TODO: distance test (only for lighting + effects!)

        r_draw_mesh(mesh->mesh);
    }

    glUseProgram(0);
}

static void effects_pass(const render_scene_t *scene)
{
    
}

// static void render_pass(const render_scene_t *scene, const render_pass_t *pass)
// {
//     setup_render_pass(pass);
    
//     // TODO: use function pointers??
//     switch (pass->type) {

//         case RENDER_PASS_GEOMETRY:
//             render_geometry(scene, pass);
//             break;

//         case RENDER_PASS_LIGHTING:
//             render_lights(scene, pass);
//             break;

//         case RENDER_PASS_SCREEN_EFFECTS:
//             render_effects(scene, pass);
//             break;
//     }
// }

void r_init_rendering()
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Color & AO, format: RGB: color rgb, A: AO
    glGenTextures(1, &tex_attachment0);
    glBindTexture(GL_TEXTURE_2D, tex_attachment0);
    glTexImage2D(GL_TEXTURE_2D
        , 0
        , GL_RGBA
        , g_window_width
        , g_window_height
        , 0
        , GL_RGBA
        , GL_UNSIGNED_BYTE, NULL);

    // Normal & Height, format: RGB: normal xyz, A: height value
    glGenTextures(1, &tex_attachment1);
    glBindTexture(GL_TEXTURE_2D, tex_attachment1);
    glTexImage2D(GL_TEXTURE_2D
        , 0
        , GL_RGBA
        , g_window_width
        , g_window_height
        , 0
        , GL_RGBA
        , GL_UNSIGNED_BYTE, NULL);

    // Properties, format: R: roughness, G: metalness, B: wetness, A: ???
    glGenTextures(1, &tex_attachment2);
    glBindTexture(GL_TEXTURE_2D, tex_attachment2);
    glTexImage2D(GL_TEXTURE_2D
        , 0
        , GL_RGBA
        , g_window_width
        , g_window_height
        , 0
        , GL_RGBA
        , GL_UNSIGNED_BYTE, NULL);

    // Depth & Stencil
    glGenTextures(1, &tex_depth);
    glBindTexture(GL_TEXTURE_2D, tex_depth);
    glTexImage2D(GL_TEXTURE_2D
        , 0
        , GL_DEPTH24_STENCIL8
        , g_window_width
        , g_window_height
        , 0
        , GL_DEPTH_STENCIL
        , GL_UNSIGNED_INT_24_8, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    // attach a texture object to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_attachment0, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tex_attachment1, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, tex_attachment2, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex_depth, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERR("there was an error creating the framebuffer object!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void r_cleanup_rendering()
{
    glDeleteTextures(1, &tex_attachment0);
    glDeleteTextures(1, &tex_attachment1);
    glDeleteTextures(1, &tex_attachment2);
    glDeleteTextures(1, &tex_depth);
    glDeleteFramebuffers(1, &framebuffer);
}

void r_render(const render_scene_t *scene)
{
    setup_rendering(scene);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    geometry_pass(scene);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(debug_gbuffers_shader);


    

    glFlush();
}