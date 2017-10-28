#include <iostream>
#include <time.h>

#include <Alex.h>

#include "graphics/TileLayer.h"

using namespace al;
using namespace graphics;
using namespace app;

#define TEST_50K 1

class Game : public Application
{
private :
	Window* m_Window;

	Shader* m_Shader1;
	Shader* m_Shader2;
	
	TileLayer* m_Layer1;
	TileLayer* m_Layer2;
public:
	Game(const char* title, int width, int height);
	~Game();

	void Init();
private:
	void OnUpdate(float delta) const override;
	void OnRender() const override;
};

Game::Game(const char* title, int width, int height)
{
	m_Window = new graphics::Window(title, width, height, this);

	m_Shader1 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	m_Shader2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	m_Layer1 = new TileLayer(m_Shader1);
	m_Layer2 = new TileLayer(m_Shader2);
}

Game::~Game()
{
	delete m_Layer1;
	delete m_Layer2;
}

void Game::Init() {
	srand(time(NULL));

#if TEST_50K
	for (float y = -9.0; y < 9.0f; y += 0.1f)
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
			m_Layer1->Add(new Sprite(x, y, 0.09f, 0.09f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
		for (float y = -9.0; y < 9.0f; y++)
			for (float x = -16.0f; x < 16.0f; x++)
				m_Layer1->Add(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#endif

	m_Layer2->Add(new Sprite(-2, -2, 4, 4, glm::vec4(0.8f, 0.2f, 0.8f, 1)));

	m_Window->Show();
}


void Game::OnUpdate(float delta) const 
{
	double x, y;
	m_Window->GetMousePosition(x, y);

	m_Shader1->Enable();
	m_Shader1->SetUniform2f("light_pos", glm::vec2(0, 0));

	m_Shader2->Enable();
	m_Shader2->SetUniform2f("light_pos", glm::vec2((float)(x * 32.0f / m_Window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / m_Window->GetHeight())));
}

void  Game::OnRender() const 
{
	m_Layer1->Render();
	m_Layer2->Render();
}

int main()
{
	Game* game = new Game("Alexzander!", 960, 540);
	
	game->Init();
	return 0;
}