#version 120

varying vec2 texCoord;
varying vec3 fragPosition;
varying vec3 fragNormal;

uniform mat4 m_Model;
uniform mat4 m_View;
uniform mat4 m_Proj;
uniform mat3 m_NormalMatrix;

void main()
{
	mat4 m_ModelView = m_View * m_Model;

	texCoord = gl_MultiTexCoord0.st;
	gl_FrontColor = gl_Color;

	gl_Position = m_Proj * m_ModelView * gl_Vertex;

	fragPosition = (m_ModelView * gl_Vertex).xyz;
	fragNormal = m_NormalMatrix * gl_Normal;
}