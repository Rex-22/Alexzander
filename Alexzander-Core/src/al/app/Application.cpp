#include "Application.h"

#include "al/graphics/layer/Layer.h"
#include <GLFW/glfw3.h>
#include "al/utils/Log.h"

namespace al { 
	using namespace graphics;

	Application::Application(const String& name, const graphics::WindowProperties& properties)
		:m_Name(name), m_Properties(properties)
	{
		window = new graphics::Window(name.c_str(), properties);
	}

	Application::~Application()
	{
		delete window;
		delete m_Timer;
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->SetWindow(window);
		m_LayerStack.push_back(layer);
		layer->OnInit();
	}

	Layer* Application::PopLayer()
	{
		Layer* layer = m_LayerStack.back();
		m_LayerStack.pop_back();
		return layer;
	}

	Layer* Application::PopLayer(Layer* layer)
	{
		for (uint i = 0; i < m_LayerStack.size(); i++)
		{
			if (m_LayerStack[i] == layer)
			{
				m_LayerStack.erase(m_LayerStack.begin() + i);
				break;
			}
		}
		return layer;
	}


	void Application::PushOverlay(Layer* layer)
	{
		layer->SetWindow(window);
		m_OverlayStack.push_back(layer);
		layer->OnInit();
	}

	Layer* Application::PopOverlay()
	{
		Layer* layer = m_OverlayStack.back();
		m_OverlayStack.pop_back();
		return layer;
	}

	Layer* Application::PopOverlay(Layer* layer)
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
		{
			if (m_OverlayStack[i] == layer)
			{
				m_OverlayStack.erase(m_OverlayStack.begin() + i);
				break;
			}
		}
		return layer;
	}

	void Application::Start()
	{
		Init();
		m_Running = true;
		m_Suspended = false;
		Run();
	}

	void Application::Suspend()
	{
		m_Suspended = true;
	}

	void Application::Resume()
	{
		m_Suspended = false;
	}

	void Application::Stop()
	{
		m_Running = false;
		AL_INFO("Stoping engine...");
	}

	void Application::Run()
	{
		m_Timer = new Timer();
		float timer = 0.0f;
		float updateTimer = m_Timer->ElapsedMillis();
		float updateTick = 1000.0f / 60.0f;
		uint frames = 0;
		uint updates = 0;
		Timestep timestep(m_Timer->ElapsedMillis());
		while (m_Running)
		{
			Window::Clear();
			float now = m_Timer->ElapsedMillis();
			
			if (now - updateTimer > updateTick)
			{
				timestep.Update(now);
				OnUpdate(timestep);
				updates++;
				updateTimer += updateTick;
				window->UpdateInput();
			}
			{
				Timer frametime;
				OnRender();
				frames++;
				m_Frametime = frametime.ElapsedMillis();
			}
			window->Update();
			if (m_Timer->Elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_FramesPerSecond = frames;
				AL_DEBUG("FPS: ", m_FramesPerSecond, " | UPS: ", m_UpdatesPerSecond);
				m_UpdatesPerSecond = updates;
				frames = 0;
				updates = 0;
				OnTick();
			}
			if (window->Closed())
				Stop();
		}	
	}

	void Application::OnTick()
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->OnTick();

		for (uint i = 0; i < m_LayerStack.size(); i++)
			m_LayerStack[i]->OnTick();
	}

	void Application::OnUpdate(const Timestep& ts)
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->OnUpdate(ts);

		for (uint i = 0; i < m_LayerStack.size(); i++)
			m_LayerStack[i]->OnUpdate(ts);
	}

	void Application::OnRender()
	{
		for (uint i = 0; i < m_LayerStack.size(); i++)
		{
			if (m_LayerStack[i]->IsVisible())
				m_LayerStack[i]->OnRender();
		}

		for (uint i = 0; i < m_OverlayStack.size(); i++)
		{
			if (m_OverlayStack[i]->IsVisible())
				m_OverlayStack[i]->OnRender();
		}
	}
	
}
