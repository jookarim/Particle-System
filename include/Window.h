#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string_view>
#include <stdexcept>

class Window
{
private:
	//member variables
	GLFWwindow* m_handle = nullptr;
	int m_width = 800, m_height = 600;
	std::string m_title = "";
private:
	//private class funcs (create, destroy)

	void createWindow(int width = 800, int height = 600, std::string_view title = "Window");
	void destroyWindow() noexcept;
public:
	//constructor

	Window();
	Window(int width = 800, int height = 600, std::string_view title = "Window");

	//destructor 
	~Window() noexcept;

	//getters 
	
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string_view getTitle() const { return m_title; }

	//disable copy/move constructors and copy/move operator(=)

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	//check if window would close
	bool shouldClose() const;
	//swap front buffer with back buffer to excute a new frame
	void swapBuffers() const;
	//a function put before checking events to enable glfw check events
	void pollEvents() const;
};