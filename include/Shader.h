#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string_view>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>

class Shader
{
private:
	GLuint m_program{};
	mutable std::unordered_map<std::string, GLuint> m_uniformCache;
private:
	std::string loadShaderFromFile(std::string_view path);

	GLint getLocation(std::string_view uniformName) const;

	void programCreated() const;
	void shaderCreated(std::string_view path, GLuint shader) const;
	  
	void createProgram(GLuint& vertexShader, GLuint& fragmentShader);
	void createProgram(GLuint& computeShader);

	void destroyProgram() noexcept;

	GLuint createShader(std::string_view path, GLenum shaderType);
	void destroyShader(GLuint& shader) noexcept;

	void validateProgram() const;

public:
	Shader(std::string_view vertexPath, std::string_view fragCode);
	Shader(std::string_view computePath);

	~Shader() noexcept;

	void bind() const;

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	void setUniformVec2(std::string_view name, const glm::vec2& value) const;
	void setUniformInt(std::string_view name, int value) const;
	void setUniformFloat(std::string_view name, float value) const;
	void setUniformVec3(std::string_view name, const glm::vec3& value) const;

	void setUniformui64(std::string_view name, GLuint64 value) const;
};