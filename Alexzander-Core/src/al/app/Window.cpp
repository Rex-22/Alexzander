#include "al/al.h"
#include "Window.h"

#include "al/graphics/TextureManager.h"

#include "al/Types.h"
#include "al/utils/Log.h"
#include "Input.h"

#include <FreeImage.h>
#include "al/graphics/renderer/IRenderer.h"
#include "al/audio/AudioEngine.h"

namespace al {
	
	using namespace graphics;

	std::map<void*, Window*> Window::s_Handles;

	Window::Window(const String& title, WindowProperties properties)
		:m_Title(title), m_Properties(properties), m_Handle(nullptr), m_Closed(false), m_EventCallback(nullptr)
	{
		AL_INFO("[Engine] Initializing window...");
		if (!Init())
		{
			AL_ERROR("[Engine] Failed base Window initialization!");
			return;
		}

		AL_INFO("[Engine] Window created");
				
		FreeImage_Initialise(TRUE);
		
		FontManager::Add(new Font("Default", "src/fonts/Jellee-Roman.ttf", 28, 0xffffff00));
		
		audio::AudioEngine::Init();

		m_InputManager = new InputManager();
	}

	Window::~Window()
	{
		FontManager::Clean();
		TextureManager::Clean();
		audio::AudioEngine::Clean();
	}

	bool Window::Init()
	{
		if(!PlatformInit())
		{
			AL_FATAL("[Engine] Failed to initialize platform!");
			return false;
		}

		Renderer::Init();

		SetTitle(m_Title);
		return true;
	}

	void Window::SetEventCallback(const WindowEventCallback& callback)
	{
		m_EventCallback = callback;
		m_InputManager->SetEventCallback(m_EventCallback);
	}

	void Window::Clear() const
	{
		Renderer::Clear();
	}

 	void Window::Update()
	{
		PlatformUpdate();
		audio::AudioEngine::Update();
	}

	bool Window::Closed() const 
	{
		return m_Closed;
	}

	void Window::RegisterWindowClass(void* handle, Window* window)
	{
		s_Handles[handle] = window;
	}

	Window* Window::GetWindowClass(void* handle)
	{
		if (handle == nullptr)
			return s_Handles.begin()->second;

		return s_Handles[handle];
	}

}
