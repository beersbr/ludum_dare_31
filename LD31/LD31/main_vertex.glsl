#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 dirLight0;

out vec3 fragColor;

void main()
{
	fragColor = vec3(1.0, 1.0, 1.0);
	gl_Position = projection * view * model * vec4(position, 1.0);
}