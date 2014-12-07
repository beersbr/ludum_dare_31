#version 330 core

uniform sampler2D tex0;

in vec2 UVc;
out vec4 finalFragColor;

void main()
{
	if( texture2D(tex0, UVc).a == 0.0){
        discard;
    }

	finalFragColor = texture2D(tex0, UVc);
}