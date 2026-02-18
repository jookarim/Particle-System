#include "ShaderStorageBuffer.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Compute
{
private:
	ShaderStorageBuffer m_positionSSBO;
	ShaderStorageBuffer m_velocitySSBO;
	unsigned int m_numParticles;

	void createSSBOs(unsigned int numParticles, const glm::vec2& startPos, const std::vector<glm::vec2>& randomVelocities);
public:
	Compute(unsigned int numParticles, const glm::vec2& startPos, const std::vector<glm::vec2>& randomVelocities);
	~Compute() noexcept = default;

	Compute(Compute&& other) noexcept;
	Compute& operator=(Compute&& other) noexcept;

	Compute(const Compute&) = delete;
	Compute& operator=(const Compute&) = delete;

	void bind() const;
	void bindPosition() const;
	void dispatch(unsigned int localSize) const;
};