#include "Window.h"

void Window::createWindow(int width, int height, std::string_view title)
{
	//check if glfw init
	if (!glfwInit()) throw std::runtime_error("Failed to init glfw");

	// put opengl context data
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window
	m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

	//check if window created
	if (!m_handle)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window\n");
	}

	//create glfw context
	glfwMakeContextCurrent(m_handle);

	//enable modern opengl
	glewExperimental = GL_TRUE;

	//check if opengl context not created
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to create opengl context");
	}

	//best practise to set viewport size

	glViewport(0, 0, m_width, m_height);
}

void Window::destroyWindow() noexcept
{
	if (!m_handle)
	{
		glfwDestroyWindow(m_handle);
		m_handle = nullptr;
	}
}

Window::Window(int width, int height, std::string_view title)
{
	//set window data

	m_width = width;
	m_height = height;
	m_title = title;

	//create window
	createWindow(m_width, m_height, m_title);
}

Window::Window()
{
	createWindow(m_width, m_height, m_title);
}

Window::~Window() noexcept
{
	destroyWindow();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_handle);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_handle);
}

void Window::pollEvents() const
{
	glfwPollEvents();
}