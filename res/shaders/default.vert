#version 120

varying vec2 TextCoord0;

varying vec3 fragPosition;
varying vec3 fragNormal;

void main()
{
	TextCoord0 = gl_MultiTexCoord0.st;
	gl_FrontColor = gl_Color;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	fragPosition = (gl_ModelViewMatrix * gl_Vertex).xyz;
	fragNormal = gl_NormalMatrix * gl_Normal;
}
