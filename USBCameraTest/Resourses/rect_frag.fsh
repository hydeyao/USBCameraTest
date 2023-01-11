#version 330 core
out vec4 rFragColor;
uniform vec4 rColor;
void main()
{
    rFragColor = rColor;
}