#version 450 core

#extension GL_ARB_bindless_texture : require

out vec4 fragColor;

uniform sampler2D diffuse;

layout(std430, binding = 2) readonly buffer Alpha
{
    float alphas[];
};

flat in uint oVertexID;

void main()
{
    vec2 uv = gl_PointCoord;
    float alpha = alphas[oVertexID];
    fragColor = vec4(texture(diffuse, uv).rgb, alpha);
}
