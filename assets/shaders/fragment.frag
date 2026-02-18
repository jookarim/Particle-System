#version 450 core

#extension GL_ARB_bindless_texture : require

out vec4 fragColor;

uniform vec3 color;
uniform sampler2D diffuse;

void main()
{
    vec2 uv = gl_PointCoord;
    fragColor = texture(diffuse, uv) * vec4(color, 1.0);
}
