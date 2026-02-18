#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh
{
private:
	GLuint m_vao{};
	unsigned int m_pointCount{};

	void createVertexArray(unsigned int numPoints);
	void destroyVertexArray() noexcept;
public:
	Mesh(unsigned int numPoints);
	~Mesh() noexcept;

	void draw() const;

	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	unsigned int getPointCount() const { return m_pointCount; }
};