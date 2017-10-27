#include <iostream>

#include <Alex.h>

#include <time.h>

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "graphics/TileLayer.h"

using namespace al;
using namespace graphics;

Window* window = new Window("Alexzander!", 960, 540);
BatchRenderer2D renderer;

Shader shader1("src/shaders/basic.vert", "src/shaders/basic.frag");
Shader shader2("src/shaders/basic.vert", "src/shaders/basic.frag");

TileLayer layer1(&shader1);
TileLayer layer2(&shader2);

float delta;

void OnUpdate(float t)
{
	delta = t;

	double x, y;
	window->GetMousePosition(x, y);

	shader1.Enable();
	shader1.SetUniform2f("light_pos", glm::vec2(0, 0));

	shader2.Enable();
	shader2.SetUniform2f("light_pos", glm::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));
	
}

void OnRender()
{
	layer1.Render();
	layer2.Render();

	/*
	renderer.Begin();
	for (int i = 0; i < sprites.size(); i++)
	{
		renderer.Submit(sprites[i]);
	}
	renderer.End();
	renderer.Flush();
	 */
}


int main()
{
	srand(time(NULL));

	for (float y = -9.0; y < 9.0f; y += 0.1)
		for (float x = -16.0f; x < 16.0f; x += 0.1)
			layer1.Add(new Sprite(x, y, 0.09f, 0.09f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));


	layer2.Add(new Sprite(-2, -2, 4, 4, glm::vec4(0.8f, 0.2f, 0.8f, 1)));

	window->SetUpdateCallback(OnUpdate);
	window->SetRenderCallback(OnRender);
	window->Show();
	return 0;
}