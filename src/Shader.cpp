#include "Shader.h"

std::string Shader::loadShaderFromFile(std::string_view path)
{
	std::ifstream shaderFile(path.data());
	
	if (!shaderFile.is_open() || !shaderFile.good())
	{
		throw std::runtime_error("Failed to create file: " + std::string(path));
	}

	std::stringstream ss;

	ss << shaderFile.rdbuf();

	std::string code = ss.str();

	return code;
}	

void Shader::shaderCreated(std::string_view path, GLuint shader) const
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar infolog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infolog);

		throw std::runtime_error("Shader: " + std::string(path) + " Had an issue:	" + infolog);
	}
}

void Shader::programCreated() const
{
	GLint success;

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar infolog[512];

		glGetProgramInfoLog(m_program, 512, nullptr, infolog);

		throw std::runtime_error("Program: Had an issue: " + std::string(infolog));
	}
}

void Shader::destroyShader(GLuint& shader) noexcept
{
	if (shader)
	{
		glDeleteShader(shader);
		shader = 0;
	}
}

void Shader::destroyProgram() noexcept
{
	if (m_program)
	{
		glDeleteProgram(m_program);
		m_program = 0;
	}
}

GLuint Shader::createShader(std::string_view path, GLenum type)
{
	GLuint shader = glCreateShader(type);
	std::string code = loadShaderFromFile(path);
	const char* code_c = code.c_str();
	glShaderSource(shader, 1, &code_c, nullptr);
	glCompileShader(shader);
	shaderCreated(path, shader);
	return shader;
}

void Shader::createProgram(GLuint& vertShader, GLuint& fragShader)
{
	m_program = glCreateProgram();
	glAttachShader(m_program, vertShader);
	glAttachShader(m_program, fragShader);
	glLinkProgram(m_program);
	destroyShader(vertShader);
	destroyShader(fragShader);
	programCreated();

#ifdef DEBUG
	validateProgram();
#endif
}

void Shader::createProgram(GLuint& computeShader)
{
	m_program = glCreateProgram();
	glAttachShader(m_program, computeShader);
	glLinkProgram(m_program);
	destroyShader(computeShader);
	programCreated();

#ifdef DEBUG
	validateProgram();
#endif
}

GLint Shader::getLocation(std::string_view uniformName) const
{
	std::string key = std::string(uniformName);

	if (m_uniformCache.find(key) != m_uniformCache.end())
	{
		return m_uniformCache.at(key);
	}

	GLint location = glGetUniformLocation(m_program, uniformName.data());

	if (location == -1)
	{
		std::cout << "Warning Failed to find uniform: " << uniformName << "\n";
		return -1;
	}

	m_uniformCache[key] = location;

	return location;
} 

Shader::Shader(std::string_view vertPath, std::string_view fragPath)
{
	m_uniformCache.clear();
	GLuint vertShader = createShader(vertPath, GL_VERTEX_SHADER);
	GLuint fragShader = createShader(fragPath, GL_FRAGMENT_SHADER);
	createProgram(vertShader, fragShader);
}

Shader::Shader(std::string_view computePath)
{
	m_uniformCache.clear();
	GLuint computeShader = createShader(computePath, GL_COMPUTE_SHADER);
	createProgram(computeShader);
}

Shader::~Shader() noexcept
{
	destroyProgram();
}

void Shader::bind() const
{
	glUseProgram(m_program);
}

void Shader::setUniformInt(std::string_view name, int value) const
{
	GLint location = getLocation(name);

	if (location != -1)
	{
		glUniform1i(location, value);
	}
}

void Shader::setUniformFloat(std::string_view name, float value) const
{
	GLint location = getLocation(name);

	if (location != -1)
	{
		glUniform1f(location, value);
	}
}

void Shader::setUniformVec2(std::string_view name, const glm::vec2& value) const
{
	GLint location = getLocation(name);

	if (location != -1)
	{
		glUniform2f(location, value.x, value.y);
	}
}

void Shader::validateProgram() const
{
	GLint success;

	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);

	if (!success)
	{
		GLchar infolog[512];

		glGetProgramInfoLog(m_program, 512, nullptr, infolog);

		throw std::runtime_error("Program Validation: Had an issue: " + std::string(infolog));
	}
}

Shader::Shader(Shader&& other) noexcept
{
	m_program = other.m_program;
	m_uniformCache = std::move(other.m_uniformCache);
	other.m_program = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		destroyProgram();

		m_program = other.m_program;
		m_uniformCache = std::move(other.m_uniformCache);

		other.m_program = 0;
	}
	return *this;
}

void Shader::setUniformVec3(std::string_view name, const glm::vec3& value) const
{
	GLint location = getLocation(name);

	if (location != -1)
	{
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
}

void Shader::setUniformui64(std::string_view name, GLuint64 value) const
{
	GLuint location = getLocation(name);

	if (location != -1)
	{
		glUniformHandleui64ARB(location, value);
	}
}
