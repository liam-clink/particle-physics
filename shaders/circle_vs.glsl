#version 400

layout(location = 0) in vec2 position; // Input vertex position attribute
out vec2 fragPos;                      // Output variable passed to the fragment shader

void main() {
    fragPos = position;                // Pass the position to the fragment shader
    gl_Position = vec4(position, 0.0, 1.0); // Set the position in clip space
}
