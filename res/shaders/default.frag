#version 120

uniform sampler2D tex0;

varying vec2 TextCoord0;

varying vec3 fragPosition;
varying vec3 fragNormal;

void main()
{
	vec3 normal = normalize(fragNormal);

	vec4 texel = texture2D(tex0, TextCoord0);

	vec3 lightDir = gl_LightSource[0].position.xyz - fragPosition;
	float d = length(lightDir);

	float lightAtten = 1.0 / (gl_LightSource[3].constantAttenuation +
		gl_LightSource[3].linearAttenuation * d +
		gl_LightSource[3].quadraticAttenuation * d * d);

	vec4 lightColor = gl_LightSource[3].ambient * gl_FrontMaterial.ambient * lightAtten;
	lightColor += 2.0 * gl_LightSource[3].diffuse * gl_FrontMaterial.diffuse * lightAtten;

	vec3 r = normalize(reflect(normalize(fragPosition.xyz), normal));

	lightColor += 3.0 * texel.a * gl_LightSource[3].specular * gl_FrontMaterial.specular * pow(max(0,dot(r, normalize(lightDir))), gl_FrontMaterial.shininess) * lightAtten;

	gl_FragColor = texel * lightColor;// + (1.0 - gl_FragCoord.w) * vec4(0.0, 0.3, 0.6, 1.0);
	gl_FragColor *= 0.80 + 0.20 * texel.a;
	gl_FragColor *= clamp(0,1,pow(gl_FragCoord.w + 0.27, 3.0));
}
