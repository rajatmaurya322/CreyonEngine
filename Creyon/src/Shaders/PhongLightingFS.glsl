#version 430 core

uniform sampler2D Tex_diffuse[4];
uniform sampler2D Tex_specular[4];

struct DirectionalLight{
	vec3 direction, ambient, diffuse, specular;
};

struct PointLight{
	vec3 position, ambient, diffuse, specular;
	float constant, linear, quadratic;
};

struct SpotLight{
	vec3 position, direction, ambient, diffuse, specular;
	float constant, linear, quadratic;
	float cutoff, outerCutoff;
};

out vec4 outputFragColor;

in vec3 normal;
in vec3 FragPos;
in vec2 Texcoords;

uniform DirectionalLight Dlight;

//All lighting calculations are done in View space(Viewer's position = {0,0,0})
vec3 calculateLight(DirectionalLight light, vec3 normal, vec3 fragPos);

vec3 calculateLight(PointLight light, vec3 normal, vec3 fragPos);

vec3 calculateLight(SpotLight light, vec3 normal, vec3 fragPos);

void main()
{
vec3 norm = normalize(normal);
vec3 fragPos = normalize(FragPos);
vec3 result = calculateLight(Dlight, norm, fragPos);

outputFragColor = vec4(result, 1.0);
}

vec3 calculateLight(DirectionalLight light, vec3 normal, vec3 fragPos){

vec3 lightDir = normalize(-light.direction);
//Diffuse shading
float diff = max(dot(lightDir, normal), 0.0);
//Specular shading
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(-fragPos, reflectDir), 0.0), 32);

vec3 ambient = light.ambient * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 diffuse = light.diffuse * diff * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 specular = light.specular * spec * vec3(texture(Tex_specular[0], Texcoords));

return ambient + diffuse + specular;
}

vec3 calculateLight(PointLight light, vec3 normal, vec3 fragPos){

vec3 lightDir = normalize(light.position - fragPos);
//Diffuse shading
float diff = max(dot(lightDir, normal), 0.0);
//Specular shading
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(-fragPos, reflectDir), 0.0), 32);
//attenuation
float fragdist = length(light.position - fragPos);
float attenuation = 1.0 / (light.constant + light.linear * fragdist + light.quadratic * fragdist
		                  * fragdist);

vec3 ambient = light.ambient * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 diffuse = light.diffuse * diff * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 specular = light.specular * spec * vec3(texture(Tex_specular[0], Texcoords));

ambient *= attenuation;
diffuse *= attenuation;
specular *= attenuation;

return ambient + diffuse + specular;
}

vec3 calculateLight(SpotLight light, vec3 normal, vec3 fragPos){

vec3 lightDir = normalize(light.position - fragPos);
//Diffuse shading
float diff = max(dot(lightDir, normal), 0.0);
//Specular shading
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(-fragPos, reflectDir), 0.0), 32);
//attenuation
float fragdist = length(light.position - fragPos);
float attenuation = 1.0 / (light.constant + light.linear * fragdist + light.quadratic * fragdist
		                  * fragdist);
//Spotlight intensity
float theta = dot(lightDir, normalize(-light.direction));
float epsilon = light.cutoff -  light.outerCutoff;
float intensity = clamp((theta - light.outerCutoff)/ epsilon, 0.0, 1.0);

vec3 ambient = light.ambient * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 diffuse = light.diffuse * diff * vec3(texture(Tex_diffuse[0], Texcoords));
vec3 specular = light.specular * spec * vec3(texture(Tex_specular[0], Texcoords));

ambient *= attenuation * intensity;
diffuse *= attenuation * intensity;
specular*= attenuation * intensity;

return ambient + diffuse + specular;
}