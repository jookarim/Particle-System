#include "Window.h"
#include <iostream>

int main()
{
	try
	{
		Window window(1270, 720, "Window");

		while (!window.shouldClose())
		{
			window.pollEvents();

			//handle events

			//clear window

			window.pollEvents();
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
}