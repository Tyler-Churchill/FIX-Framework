#version 330

in vec2 vertTexCoord;
out vec2 fragTexCoord;

layout(location = 0)in vec4 position;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
 
    fragTexCoord = vertTexCoord;
    //projection * view * transfrom
    gl_Position =   transformationMatrix * position;
}