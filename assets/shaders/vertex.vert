#version 450 core

layout(std430, binding = 0) readonly buffer Points
{
	vec2 points[];
};

void main()
{
	uint vertexID = gl_VertexID;
	
	vec2 point = points[vertexID];

	gl_Position = vec4(point.x, point.y, 0.f, 1.f);

	gl_PointSize = 10;
}