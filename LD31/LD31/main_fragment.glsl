#version 330 core

uniform sampler2D tex0;

in vec2 UVc;
in vec3 c;
out vec4 finalFragColor;

void main()
{
	if( texture2D(tex0, UVc).a == 0.0){
        discard;
    }

	vec3 colorMix = mix(c, texture2D(tex0, UVc).rgb, 1.0);
	finalFragColor = vec4(colorMix, texture2D(tex0, UVc).a);
}