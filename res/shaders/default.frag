#version 120

/**
 * gl_LightSource[1] - flash light settings
 * gl_LightSource[2] - teapot light
 * gl_LightSource[3] - candle light settings
 * gl_LightSource[4] - terror light settings
 * gl_LightSource[5] - entrance of deathzone
 * gl_LightSource[7] - party light settings
 **/

uniform sampler2D tex_albedo;
// uniform sampler2D tex_normal;
// uniform sampler2D tex_roughness;
// uniform sampler2D tex_ao;

varying vec2 texCoord;
varying vec3 fragPosition;
varying vec3 fragNormal;

void main()
{
	vec3 n = normalize(fragNormal);
	vec3 l = gl_LightSource[0].position.xyz - fragPosition;
	float d = length(l);

	vec4 color = texture2D(tex_albedo, texCoord);

	float lightAtten = 1.0 / (gl_LightSource[3].constantAttenuation +
		gl_LightSource[3].linearAttenuation * d +
		gl_LightSource[3].quadraticAttenuation * d * d);

	vec4 lightColor = gl_LightSource[3].ambient * gl_FrontMaterial.ambient * lightAtten;
	lightColor += 2.0 * gl_LightSource[3].diffuse * gl_FrontMaterial.diffuse * lightAtten;

	vec3 r = normalize(reflect(normalize(fragPosition.xyz), normalize(n.xyz)));

	lightColor += 3.0 * color.a * gl_LightSource[3].specular * gl_FrontMaterial.specular * pow(max(0,dot(r, normalize(l))), gl_FrontMaterial.shininess) * lightAtten;

	gl_FragColor = color * lightColor;// + (1.0 - gl_FragCoord.w) * vec4(0.0, 0.3, 0.6, 1.0);
	gl_FragColor *= 0.80 + 0.20 * color.a;
	gl_FragColor *= clamp(0,1,pow(gl_FragCoord.w + 0.27, 3.0));
}
