#include "Test2D.h"
#include "glm/gtc/matrix_transform.inl"

using namespace al;
using namespace graphics;
using namespace events;
using namespace audio;
using namespace glm;

Test2D::Test2D()
	: Layer2D(ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

void Test2D::OnInit(Renderer2D& renderer)
{
	TextureManager::Add(new Texture("Text1", "src/textures/test1.png"));
	TextureManager::Add(new Texture("Text2", "src/textures/test2.png"));
	TextureManager::Add(new Texture("Text3", "src/textures/test3.png"));

	for (float y = -9.0; y < 9.0f; y++)
		for (float x = -16.0f; x < 16.0f; x++)
		{
			int r = rand() % 256;

			int col = 0xffff00 << 8 | r;

			if (rand() % 4 == 0)
				Add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
				Add(new Sprite(x, y, 0.9f, 0.9f, TextureManager::Get("Text" + std::to_string(rand() % 3 + 1))));
		}
	
	g = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-15.8f, 7.0f, 0.0f)));
	m_FPS = new Label("Greetings!", 0.4f, 0.4f, FontManager::Get("Default"));
	g->Add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->Add(m_FPS);

	Submit(g);

	AudioEngine::Add(new Sound("Test", "src/sound/FromHere.ogg"));
}

void Test2D::OnRender(Renderer2D& renderer)
{
	//Submit(g);
}

void Test2D::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(METHOD(&Test2D::OnKeyPressedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(METHOD(&Test2D::OnMouseMovedEvent));
}

bool Test2D::OnKeyPressedEvent(KeyPressedEvent& event)
{
	switch (event.GetKeyCode())
	{
	case AL_KEY_UP:
	{
		if (event.GetRepeat())
		{
			gain += 0.05f;
			AudioEngine::Get("Test")->SetGain(gain);
			return true;
		}

	}
	case AL_KEY_DOWN:
	{
		if (event.GetRepeat())
		{
			gain -= 0.05f;
			AudioEngine::Get("Test")->SetGain(gain);
			return true;
		}
	}
	}

	if (event.GetRepeat())
		return false;

	switch (event.GetKeyCode())
	{
	case AL_KEY_P:
		AudioEngine::Get("Test")->Play();
		return true;
	case AL_KEY_S:
		AudioEngine::Get("Test")->Stop();
		return true;
	case AL_KEY_L:
		AudioEngine::Get("Test")->Loop();
		return true;
	case AL_KEY_1:
		AudioEngine::Get("Test")->Pause();
		return true;
	case AL_KEY_2:
		AudioEngine::Get("Test")->Resume();
		return true;
	default:
		return false;
	}
}

bool Test2D::OnMouseMovedEvent(MouseMovedEvent& event)
{
	const Shader *shader = m_Renderer->GetShader();
	vec2 mouse = event.GetPosition();

	shader->Enable();
	shader->SetUniform2f("light_pos", vec2((float)(mouse.x * 32.0f / m_Window->GetWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / m_Window->GetHeight())));
	shader->Disable();

	return false;
}

