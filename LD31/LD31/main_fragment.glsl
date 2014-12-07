#version 330 core

uniform sampler2D tex0;

in vec2 UVc;
out vec3 finalFragColor;

void main()
{
	finalFragColor = texture2D(tex0, UVc).rgb;
}