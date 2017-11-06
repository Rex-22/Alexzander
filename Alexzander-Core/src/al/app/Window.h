#pragma once

#include "al/al.h"

#include "al/graphics/FontManager.h"
#include "al/audio/AudioEngine.h"
#include "al/graphics/TextureManager.h"

#include "al/events/Events.h"

#include "al/app/Input.h"

namespace al {
	
	typedef std::function<void(events::Event& event)> WindowEventCallback;

	struct AL_API WindowProperties
	{
		int width, height;
		bool vsync;
	};

	class AL_API Window
	{
	private:
		static std::map<void*, Window*> s_Handles;
	private:
		String m_Title;
		WindowProperties m_Properties;
		void *m_Handle;
		bool m_Closed;

		WindowEventCallback m_EventCallback;
		InputManager* m_InputManager;
	public:
		Window(const String& name, WindowProperties properties);
		~Window();

		void Clear() const;
		void Update();
		bool Closed() const;

		void SetTitle(const String& title);

		inline int GetWidth() const { return m_Properties.width; }
		inline int GetHeight() const { return m_Properties.height; }

		void SetVsync(bool enabled);
		inline bool IsVsync() const { return m_Properties.vsync; }

		inline InputManager* GetInputManager() const { return m_InputManager; }

		void SetEventCallback(const WindowEventCallback& callback);
	private:
		bool Init();

		bool PlatformInit();
		void PlatformUpdate();

		friend void ResizeCallback(Window* window, int32 width, int32 height);
		friend void FocusCallback(Window* window, bool focused);

	public:
		static void RegisterWindowClass(void* handle, Window* window);
		static Window* GetWindowClass(void* handle);
	};

}