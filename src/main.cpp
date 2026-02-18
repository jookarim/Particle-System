#include "Window.h"
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "ShaderStorageBuffer.h"
#include "Compute.h"
#include "Random.h"
#include "Texture.h"

int main()
{
	try
	{
		Window window(1270, 720, "Window");
		
		Shader computeShader("assets/shaders/compute.comp");
		Shader appShader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
		
		std::vector<glm::vec2> velocities(10000);

		for (size_t i = 0; i < velocities.size(); ++i)
		{
			velocities[i] = glm::vec2(
				generateRandom(-0.2f, 0.2f),
				generateRandom(-0.2f, 0.2f)
			);
		}

		Mesh mesh(10000);
		Compute compute(10000, { 0.f, 0.f }, velocities);
		Texture texture("assets/images/bricks2.jpg");

		texture.makeResident();

		float lastTime = glfwGetTime();
		float deltaTime = 0.f;

		while (!window.shouldClose())
		{
			float currTime = glfwGetTime();
			deltaTime = currTime - lastTime;
			lastTime = currTime;

			window.pollEvents();

			computeShader.bind();
			computeShader.setUniformFloat("dt", deltaTime);
			computeShader.setUniformInt("numParticles", static_cast<int>(10000));
			computeShader.setUniformFloat("speed", 10.f);

			compute.bind();
			compute.dispatch(256);
		
			window.clear(1.f, 0.f, 0.f, 1.f);

			appShader.bind();
			appShader.setUniformui64("diffuse", texture.getHandle());
			compute.bindAlpha();

			mesh.draw();

			window.swapBuffers();
		}
	}

	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}