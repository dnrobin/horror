#version 120

varying vec2 texCoord;
varying vec3 fragPosition;
varying vec3 fragNormal;

void main()
{
	texCoord = gl_MultiTexCoord0.st;
	gl_FrontColor = gl_Color;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	fragPosition = (gl_ModelViewMatrix * gl_Vertex).xyz;
	fragNormal = gl_NormalMatrix * gl_Normal;
}
