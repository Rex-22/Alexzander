#pragma once

#include "al/Common.h"
#include "al/graphics/FontManager.h"

#include "al/audio/AudioEngine.h"
#include "al/utils/Log.h"

#include "gl/gl.h"
#include "Input.h"

struct GLFWwindow;

namespace al {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32
	
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
	private:
		friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		friend void WindowResizeCallback(GLFWwindow *window, int width, int height);
		friend void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
	public:
		inline static void GLErrorCheck()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				AL_ERROR("[Engine] OpenGL Error: ", error);
		}
	};

}