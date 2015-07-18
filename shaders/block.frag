#version 330 core
in vec3 TexCoord;

out vec4 color;

uniform sampler2DArray ourTexture;

void main()
{
    color = texture(ourTexture, vec3(TexCoord.x, TexCoord.y, max(0, min(31, floor(TexCoord.z + 0.5))) ));
}
