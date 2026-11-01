#version 460 core
layout(location = 0) in vec3 vp;
uniform vec2 offset;
uniform float angle;
void main() {
    float c = cos(angle), s = sin(angle);
    vec2 p = mat2(c, -s, s, c) * vp.xy;
    gl_Position = vec4(p + offset, vp.z, 1.0);
}