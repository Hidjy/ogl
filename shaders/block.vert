#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 texCoord;

out vec3 TexCoord;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position, 1.0f);
	TexCoord = vec3(texCoord.x, 1.0 - texCoord.y, texCoord.z);
}
