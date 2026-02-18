#version 450 core

layout(std430, binding = 0) readonly buffer Positions
{
	vec2 positions[];
};

layout(std430, binding = 2) readonly buffer Alpha
{
	float alphas[];
};

flat out uint oVertexID;

void main()
{
	uint vertexID = gl_VertexID;
	
	vec2 position = positions[vertexID];

	gl_Position = vec4(position.x, position.y, 0.f, 1.f);

	gl_PointSize = 10;

	oVertexID = vertexID;
}