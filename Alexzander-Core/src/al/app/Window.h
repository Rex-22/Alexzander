#pragma once

#include "al/Common.h"
#include "al/graphics/FontManager.h"

#include "al/audio/AudioEngine.h"
#include "al/utils/Log.h"

#include "al/events/Events.h"


#include "gl/gl.h"
#include "Input.h"

struct GLFWwindow;

namespace al {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32
	
	typedef std::function<void(events::Event& event)> WindowEventCallback;

	struct AL_API WindowProperties
	{
		int width, height;
		bool vsync;
	};

	class AL_API Window
	{
	public:
		static GLFWwindow* s_Instance;
	private:
		String m_Title;
		WindowProperties m_Properties;
		GLFWwindow *m_Window;
		bool m_Closed;

		WindowEventCallback m_EventCallback;
		InputManager* m_InputManager;
	public:
		Window(const String& name, WindowProperties properties);
		~Window();
		inline static GLFWwindow* GetCallback() { return s_Instance; }

		static void Clear();
		void Update();
		bool Closed();

		void SetTitle(const String& title);

		inline int GetWidth() const { return m_Properties.width; }
		inline int GetHeight() const { return m_Properties.height; }

		inline bool IsVsyncEnabled() const { return m_Properties.vsync; }
		void SetVsync(bool enabled);
		
		inline InputManager* GetInputManager() const { return m_InputManager; }

		void SetEventCallback(const WindowEventCallback& callback);
	private:
		friend void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend void GLFWCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		friend void GLFWWindowResizeCallback(GLFWwindow *window, int width, int height);
		friend void GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height);
		friend void GLFWFocusCallback(GLFWwindow *window, int focused);

		friend void ResizeCallback(Window* window, int32 width, int32 height);
		friend void FocusCallback(Window* window, bool focused);
	public:
		inline static void GLErrorCheck()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				AL_ERROR("[Engine] OpenGL Error: ", error);
		}
	};

}