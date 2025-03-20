#version 330

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 vertex_tangent;
layout(location = 3) in vec2 vertex_texcoords;
layout(location = 4) in vec4 vertex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 frag_position;
out vec4 frag_color;
out vec3 frag_normal;
out vec3 frag_tangent;
out vec3 frag_bitangent;
out vec2 frag_texcoords;

void main()
{
    gl_Position = proj * view * model * vec4(vertex_position, 1.0);
    frag_position = gl_Position.xyz;

    frag_color = vertex_color;
    frag_normal = normalize(vertex_normal);     // TODO: transform it
    frag_tangent = normalize(vertex_tangent);   // TODO: transform it
    frag_bitangent = normalize(cross(vertex_tangent, vertex_normal));
    frag_texcoords = vertex_texcoords;
}