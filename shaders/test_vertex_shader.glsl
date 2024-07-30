#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) out vec3 fragment_color;

void main()
{
    fragment_color = vertex_color;
    gl_Position = vec4(position, 1.0); // The 1.0 at the end means to not calculate perspective
}