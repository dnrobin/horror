#version 330

uniform mat4 m_Model;
uniform mat4 m_View;
uniform mat4 m_Proj;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_tangent;
layout(location = 2) in vec3 v_normal;
layout(location = 3) in vec3 v_color;

out Vertex {
    vec4 position;
    vec3 color;
} v;

void main() {
    v.position = m_Proj * m_View * m_Model * vec4(v_position, 1);
    v.color = color;
}