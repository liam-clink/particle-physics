#version 400
// The main color buffer is location 0
// This just draws directly to the frame buffer

layout(location = 2) in vec3 color;
out vec4 fragment_color;

void main()
{
    fragment_color = vec4(color, 1.0);
}