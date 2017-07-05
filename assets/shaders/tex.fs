#version 330

in vec2 fragTexCoord;
uniform sampler2D tex;
out vec4 finalColor;
void main()
{
	finalColor = texture(tex, fragTexCoord);	
	//finalColor = vec4(1.0, 1.0, 0.25, 1.0);
}