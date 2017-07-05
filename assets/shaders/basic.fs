#version 130

in vec4 color;

out vec4 fColor;

void main()
{
	//gl_FragColor = vec4(1.0, 0.3, 1.0, 1.0);	
	fColor = color;
}