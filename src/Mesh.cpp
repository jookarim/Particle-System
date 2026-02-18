#include "Mesh.h"

void Mesh::createVertexArray(unsigned int numPoints)
{
	m_pointCount = numPoints;
	glCreateVertexArrays(1, &m_vao);
}

void Mesh::destroyVertexArray() noexcept
{ 
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
}

Mesh::Mesh(unsigned int numPoints)
{
	createVertexArray(numPoints);
}

Mesh::~Mesh() noexcept
{
	destroyVertexArray();
}

void Mesh::draw() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_POINTS, 0, m_pointCount);
}

Mesh::Mesh(Mesh&& other) noexcept
{
	m_pointCount = other.m_pointCount;
	m_vao = other.m_vao;

	other.m_pointCount = 0;
	other.m_vao = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this == &other) return *this;
	destroyVertexArray();
	m_pointCount = other.m_pointCount;
	m_vao = other.m_vao;
	other.m_pointCount = 0;
	other.m_vao = 0;
	return *this;
}