#include "Compute.h"

void Compute::createSSBOs(unsigned int numParticles, const glm::vec2& startPos, const std::vector<glm::vec2>& randomVertices)
{
	std::vector<glm::vec2> positions(numParticles, startPos);
	std::vector<float> transparency(numParticles, 1.f);

	m_positionSSBO = ShaderStorageBuffer(numParticles * sizeof(glm::vec2), 0, positions.data());
	m_velocitySSBO = ShaderStorageBuffer(numParticles * sizeof(glm::vec2), 1, randomVertices.data());
	m_alphaSSBO = ShaderStorageBuffer(numParticles * sizeof(float), 2, transparency.data());
	m_numParticles = numParticles;
}

Compute::Compute(unsigned int numParticles, const glm::vec2& startPos, const std::vector<glm::vec2>& randomVertices)
{
	createSSBOs(numParticles, startPos, randomVertices);
}

Compute::Compute(Compute&& other) noexcept
{
	m_numParticles = other.m_numParticles;
	m_positionSSBO = std::move(other.m_positionSSBO);
	m_velocitySSBO = std::move(other.m_velocitySSBO);
	m_alphaSSBO = std::move(other.m_alphaSSBO);

	other.m_numParticles = 0;
}

Compute& Compute::operator=(Compute&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	m_numParticles = other.m_numParticles;
	m_positionSSBO = std::move(other.m_positionSSBO);
	m_velocitySSBO = std::move(other.m_velocitySSBO);
	m_alphaSSBO = std::move(other.m_alphaSSBO);
	other.m_numParticles = 0;

	return *this;
}

void Compute::bind() const
{
	m_positionSSBO.bind();
	m_velocitySSBO.bind();
	m_alphaSSBO.bind();
}

void Compute::bindPosition() const
{
	m_positionSSBO.bind();
}

void Compute::dispatch(unsigned int localSize) const
{
	glDispatchCompute((m_numParticles + localSize - 1) / localSize, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Compute::bindAlpha() const
{
	m_alphaSSBO.bind();
}