#include "ShaderStorageBuffer.h"

void ShaderStorageBuffer::createBuffer(unsigned int allocateSize, unsigned int bindingPoint,const void* data)
{
	m_size = allocateSize;
	glCreateBuffers(1, &m_ssbo);
	glNamedBufferStorage(m_ssbo, allocateSize, data, GL_DYNAMIC_STORAGE_BIT);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_ssbo);
}

void ShaderStorageBuffer::destroyBuffer() noexcept
{
	if (m_ssbo)
	{
		glDeleteBuffers(1, &m_ssbo);
		m_ssbo = 0;
	}
}

ShaderStorageBuffer::ShaderStorageBuffer(unsigned int allocateSize, unsigned int bindingPoint, const void* data)
{
	createBuffer(allocateSize, bindingPoint, data);
}

ShaderStorageBuffer::~ShaderStorageBuffer() noexcept
{
	destroyBuffer();
}

void ShaderStorageBuffer::bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
}

void* ShaderStorageBuffer::getData() const
{
	void* data = malloc(m_size);

	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, m_size, data);

	return data;
}

void ShaderStorageBuffer::uploadData(int offset, const void* data)
{
	glNamedBufferSubData(m_ssbo, 0, m_size, data);
}

ShaderStorageBuffer::ShaderStorageBuffer(ShaderStorageBuffer&& other) noexcept
{
	m_size = other.m_size;
	m_ssbo = other.m_ssbo;
	other.m_size = 0;
	other.m_ssbo = 0;
}

ShaderStorageBuffer& ShaderStorageBuffer::operator=(ShaderStorageBuffer&& other) noexcept
{
	if (this == &other) return *this;
	destroyBuffer();
	m_size = other.m_size;
	m_ssbo = other.m_ssbo;
	other.m_size = 0;
	other.m_ssbo = 0;
	return *this;
}