#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
uniform mat4 u_transformMat4;

void main() {
    gl_Position = u_transformMat4 * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    texCoord = aTexCoord;
}