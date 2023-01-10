#version 330 core
layout (location = 0) in vec3 rPos;
void main()
{
    gl_Position = vec4(rPos.x, rPos.y, rPos.z, 1.0);
}