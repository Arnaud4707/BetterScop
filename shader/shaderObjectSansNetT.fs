
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D t;
uniform vec3 color;
uniform float glow;
uniform float factor;

void main()
{

    float r = fract(gl_PrimitiveID * 0.137);
    float g = fract(gl_PrimitiveID * 0.517);
    float b = fract(gl_PrimitiveID * 0.731);
    vec3 c = vec3(r, g, b);
    vec3 ct = texture(t , TexCoords).rgb;
    vec3 objColor = color;
    objColor += glow * vec3(1.0, 0.9, 0.8);
    vec3 cc = mix(color, ct, factor);

    FragColor = vec4(cc, 1.0);
}