#include "Compute.h"

void Compute::createSSBOs(unsigned int numParticles, const glm::vec2& startPos, const std::vector<glm::vec2>& randomVertices)
{
	std::vector<glm::vec2> positions(numParticles, startPos);
	m_positionSSBO = ShaderStorageBuffer(numParticles * sizeof(glm::vec2), 0, positions.data());
	m_velocitySSBO = ShaderStorageBuffer(numParticles * sizeof(glm::vec2), 1, randomVertices.data());
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
	other.m_numParticles = 0;

	return *this;
}

void Compute::bind() const
{
	m_positionSSBO.bind();
	m_velocitySSBO.bind();
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