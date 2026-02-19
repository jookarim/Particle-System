#pragma once

#include <GL/glew.h>
#include <cstdlib>
#include <vector>

class ShaderStorageBuffer
{
private:
	GLuint m_ssbo;
	int m_size = 0;

	void createBuffer(unsigned int allocateSize, unsigned int bindingPoint,const void* data);
	void destroyBuffer() noexcept;
public:
	ShaderStorageBuffer() = default;

	ShaderStorageBuffer(unsigned int allocateSize, unsigned int bindingPoint ,const void* data);
	~ShaderStorageBuffer() noexcept;

	ShaderStorageBuffer(ShaderStorageBuffer&& other) noexcept;
	ShaderStorageBuffer& operator=(ShaderStorageBuffer&& other) noexcept;

	ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
	ShaderStorageBuffer& operator=(const ShaderStorageBuffer&) = delete;

	void uploadData(int offset, const void* data);
	void bind() const;

	int getSize() const { return m_size; }
	std::vector<char> getData() const;

	unsigned int readUInt() const;
};