#version 330 core
in vec3 TexCoord;

out vec4 color;

uniform sampler2DArray ourTexture;

void main()
{
    color = texture(ourTexture, TexCoord);
}
