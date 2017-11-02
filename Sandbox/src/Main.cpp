#include <iostream>

#include <Alex.h>

#include "graphics/TileLayer.h"
#include "glm/gtc/matrix_transform.hpp"

#include <time.h>

using namespace al;
using namespace graphics;
using namespace app;

#define TEST_50K 1

class Game : public Application
{
private :
	Window* m_Window;

	Shader* m_Shader;
	
	TileLayer* m_Layer;

	Texture* textures[3];

	Label* m_FPS;
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

	m_Shader = new Shader("src/shaders/basic.shader");

	m_Layer = new TileLayer(m_Shader);

	textures[0] = new Texture("src/textures/test1.png");
	textures[1] = new Texture("src/textures/test2.png");
	textures[2] = new Texture("src/textures/test3.png");
}

Game::~Game()
{
	delete m_Layer;	   
	for (int i = 0; i < 3; i++)
		delete textures[i];
}

void Game::Init() {
	srand(time(NULL));

	int texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	m_Shader->Enable();
	m_Shader->SetUniform1iv("textures", texIDs, 10);
#if TEST_50K

	for (float y = -9.0; y < 9.0f; y ++)
		for (float x = -16.0f; x < 16.0f; x ++)
		{
			if (rand() % 4 == 0)
				 m_Layer->Add(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				m_Layer->Add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
#else
	Sprite* sprite = new Sprite(1.0f, 1.0f, 5.0f, 5.0f, {1.0f, 0.0f, 1.0f, 1.0f});

	m_Layer1->Add(sprite);
#endif

	Group* g = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-15.8f, 7.0f, 0.0f)));
	m_FPS = new Label("", 0.4f, 0.4f, FontManager::Get("Jellee-Roman.ttf"));
	g->Add(new Sprite(0, 0, 5, 1.5f, glm::vec4(0.3f, 0.3f, 0.3f, 0.9f)));
	g->Add(m_FPS);

	m_Layer->Add(g);


	m_Window->Show();
}


void Game::OnUpdate(float delta) const 
{
	double x, y;
	m_Window->GetMousePosition(x, y);

	m_Shader->Enable();
	m_Shader->SetUniform2f("light_pos", glm::vec2((float)(x * 32.0f / m_Window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / m_Window->GetHeight())));
	m_FPS->SetText(std::to_string(m_Frames) + " fps");
}

void  Game::OnRender() const 
{
	m_Layer->Render();
}

int main()
{
	Game* game = new Game("Alexzander!", 960, 540);
	
	game->Init();
	return 0;
}
