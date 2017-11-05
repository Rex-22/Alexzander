#pragma once

#include "al/Common.h"

#include "Window.h"
#include "al/utils/Timestep.h"
#include "al/utils/Timer.h"
#include "al/graphics/layer/Layer.h"

namespace al {
	
	class AL_API Application
	{
	private:
		static Application* s_Instance;
	public :
		Window* window;
	protected:
		bool m_Running, m_Suspended;
		Timer* m_Timer;
		uint m_UpdatesPerSecond, m_FramesPerSecond;
		float m_Frametime;

		String m_Name;
		WindowProperties m_Properties;

		std::vector<graphics::Layer*> m_LayerStack;
		std::vector<graphics::Layer*> m_OverlayStack;
	public:
		Application(const String& name, const WindowProperties& properties);
		virtual ~Application();

		virtual void Init() {}

		void PushLayer(graphics::Layer* layer);
		graphics::Layer* PopLayer();
		graphics::Layer* PopLayer(graphics::Layer* layer);

		void PushOverlay(graphics::Layer* layer);
		graphics::Layer* PopOverlay();
		graphics::Layer* PopOverlay(graphics::Layer* layer);

		void Start();
		void Suspend();
		void Resume();
		void Stop();

		inline uint GetFPS() const { return m_FramesPerSecond; }
		inline uint GetUPS() const { return m_UpdatesPerSecond; }
		inline float GetFrametime() const { return m_Frametime; }

		inline uint GetWindowWidth() const { return window->GetWidth(); }
		inline uint GetWindowHeight() const { return window->GetHeight(); }
		inline glm::vec2 GetWindowSize() const { return glm::vec2((float)window->GetWidth(), (float)window->GetHeight()); }

		
	private:
		void Run(); 

		void OnUpdate(const Timestep& ts);
		void OnTick();
		void OnRender();
	private:
		void OnEvent(events::Event& event);
	public:
		inline static Application& GetApplication() { return *s_Instance; }
	};

}
