#version 330 core
layout (location = 0) in vec3 dPos;
void main()
{
    gl_Position = vec4(dPos.x, dPos.y, dPos.z, 1.0);
}