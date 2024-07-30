#version 400

in vec2 fragPos;
out vec4 color;

uniform vec2 center;
uniform float radius;
uniform vec3 circleColor;

void main() {
    float dist = distance(fragPos, center);
    if (dist < radius) {
        color = vec4(circleColor, 1.0);
    } else {
        discard;  // Discard the fragment if it's outside the circle
    }
}
