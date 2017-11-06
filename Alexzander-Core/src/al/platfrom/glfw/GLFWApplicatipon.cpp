#include "al/al.h"
#include "al/app/Application.h"
#include "al/utils/Log.h"

#include "al/utils/Timestep.h"

namespace al {
	
	Application::Application(const String& name, const WindowProperties& properties)
		:m_Name(name), m_Properties(properties), m_Frametime(0.0f)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::PlatformInit()
	{
		window = new Window(m_Name, m_Properties);
		window->SetEventCallback(METHOD(&Application::OnEvent));
	}

	void Application::Start()
	{
		AL_INFO("Starting engine...");
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
			window->Clear();
			float now = m_Timer->ElapsedMillis();

			if (now - updateTimer > updateTick)
			{
				timestep.Update(now);
				OnUpdate(timestep);
				updates++;
				updateTimer += updateTick;
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
				m_UpdatesPerSecond = updates;
				AL_DEBUG("FPS: ", m_FramesPerSecond, " | UPS: ", m_UpdatesPerSecond);
				frames = 0;
				updates = 0;
				OnTick();
			}
			if (window->Closed())
				Stop();
		}
	}



}