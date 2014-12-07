#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;
layout(location = 4) in mat4 m;

uniform mat4 projection;
uniform mat4 view;
// uniform mat4 model;


// uniform vec3 dirLight0;

out vec2 UVc;
out vec3 c;

void main()
{
	UVc = uv;
	c = color;
	gl_Position = projection * view * mat4(1.0) * vec4(position, 1.0);
}