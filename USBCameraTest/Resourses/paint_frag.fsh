#version 330 core
out vec4 dFragColor;
uniform vec4 ourColor;
void main()
{
    dFragColor = ourColor;
}