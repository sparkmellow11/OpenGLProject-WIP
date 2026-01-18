#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform vec4 tintColor;


void main()
{
    FragColor = texture(texture_diffuse1, texCoords);
    FragColor = FragColor * tintColor;
}