#include <GL/glew.h>
#include "stb/stb_image.h"
#include <string_view>
#include <stdexcept>
#include <cmath>

class Texture
{
private:
	GLuint m_id{};
	GLuint64 m_handle{};

	void loadFromFile(std::string_view path);
	void destroy() noexcept;
public:
	Texture(std::string_view path);
	~Texture() noexcept;

	void bind(unsigned int bindingIndex);

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	
	GLuint getHandle() const { return m_handle; }
	void makeResident();
};