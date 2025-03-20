#version 330

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;




uniform float time;

in vec3 frag_position;

in vec4 frag_color;
in vec3 frag_normal;
in vec3 frag_tangent;
in vec3 frag_bitangent;
in vec2 frag_texcoords;

uniform sampler2D albedo_map;       // RGB:rgb, A: transparency
uniform sampler2D normal_map;       // R: n.x, G: n.y, B: n.z, A: height
uniform sampler2D surface_map;      // R: metalness, G: roughness, B: wetness, A: ambient_occlusion

uniform vec3 light_position;
uniform vec3 light_direction;
uniform vec3 eye_position;

out vec4 color;

void main()
{
    // Sample textures
    vec4 albedo_value = texture(albedo_map, frag_texcoords);
    vec4 normal_value = texture(normal_map, frag_texcoords);
    vec4 surface_value = texture(surface_map, frag_texcoords);

    // extract surface properties
    vec3 albedo = albedo_value.rgb;
    bool mask = albedo_value.a > 0;
    vec3 normal = normalize(normal_value.xyz);
    float height = normal_value.a;
    float metalness = surface_value.r;
    float roughness = surface_value.g;
    float wetness = surface_value.b;
    float ambient_occlusion = surface_value.a;

    // Calculate lighting
    vec3 lightDir = normalize(light_position - frag_position);
    vec3 viewDir = normalize(eye_position - frag_position);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float NdotL = max(dot(normal, lightDir), 0.0);
    float NdotH = max(dot(normal, halfwayDir), 0.0);
    float spec = pow(NdotH, 32.0);

    vec3 ambient = 0.1 * albedo.rgb;
    vec3 diffuse = NdotL * albedo.rgb;
    vec3 specular = vec3(wetness * spec);

    // color = vec4(ambient + diffuse + specular, albedo.a);
    color = vec4(1.0, 0.0, 0.0, 1.0);
}