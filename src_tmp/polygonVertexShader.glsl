#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

out vec3 fragmentColor;

void main() {
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
    fragmentColor = color;
}