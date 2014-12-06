#version 330 core

in vec3 fragColor;
out vec4 finalFragColor;

void main()
{
	finalFragColor = vec4(fragColor, 1.0);
}