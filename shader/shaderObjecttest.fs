
#version 330 core
out vec4 FragColor;

struct lightning {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct textu {
    sampler2D diffuse; 
    sampler2D specular; 
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;

uniform textu t;  
uniform vec3 viewPos;
uniform lightning material[32];
uniform lightning lightObj;
uniform Light light;

void main()
{
    vec3 ambient = light.ambient * material[0].ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material[0].diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material[0].shininess);
    vec3 specular = light.specular * (spec * material[0].specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}