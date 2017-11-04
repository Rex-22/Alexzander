#include "Window.h"

#include <GLFW/glfw3.h>

#include <FreeImage.h>
#include "al/Types.h"

#include "gl/gl.h"
#include "TextureManager.h"
#include "al/utils/Log.h"

namespace al { namespace graphics {

	Window::Window(const String& title, WindowProperties properties)
		:m_Title(title), m_Properties(properties)
	{

		ClearKeys();
		AL_INFO("[Engine] Initializing window...");
		if (!glfwInit())
		{
			AL_ERROR("[Engine] Failed to initialize GLFW!");
		}
		m_Window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			AL_ERROR("[Engine] Failed to create GLFW window!");
		}

		AL_INFO("[Engine] Window created");

		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xp = (vidmode->width - m_Properties.width) / 2;
		int yp = (vidmode->height - m_Properties.height) / 2;

		glfwSetWindowPos(m_Window, xp, yp);

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);

		glfwSwapInterval(m_Properties.vsync);

		AL_INFO("[Engine] Initializing GLEW...");
		if (glewInit() != GLEW_OK)
		{
			AL_ERROR("[Engine] Failed to initialize GLEW!");
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		AL_INFO("[Engine] OpenGL ", glGetString(GL_VERSION));

		FreeImage_Initialise(TRUE);
		FontManager::Add(new Font("Default", "src/fonts/Jellee-Roman.ttf", 28, 0xffffff00));

		audio::AudioEngine::Init();
	}

	Window::~Window()
	{
		audio::AudioEngine::Clean();
		graphics::TextureManager::Clean();
		glfwTerminate();
	}
	
	void Window::GLErrorCheck()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			AL_ERROR("[Engine] OpenGL Error: ", error);
	}

	void Window::SetVsync(bool enabled)
	{
		m_Properties.vsync = enabled; 
		glfwSwapInterval(enabled); 
	}

	bool Window::IsKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			AL_WARN("[Input] Keycode '", keycode, "' is out of range!");
			return false;
		}

		return m_Keys[keycode];
	}

	bool Window::IsKeyTyped(unsigned keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			AL_WARN("[Input] Keycode '", keycode, "' is out of range!");
			return false;
		}

		return m_KeyTyped[keycode];
	}

	bool Window::IsMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
		{
			AL_WARN("[Input] Mouse button '", button, "' is out of range!");
			return false;
		}

		return m_MouseButtons[button];
	}

	bool Window::IsMouseClicked(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
		{
			AL_WARN("[Input] Mouse button '", button, "' is out of range!");
			return false;
		}
	
		return m_MouseClicked[button];
	}

	glm::vec2 Window::GetMousePosition() const
	{
		return { mx, my };
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

 	void Window::Update()
	{
		GLErrorCheck();
		

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		audio::AudioEngine::Update();
	}

	void Window::UpdateInput()
	{
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	bool Window::Closed()
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void WindowResizeCallback(GLFWwindow *window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		win->m_Properties.width = width;
		win->m_Properties.height= height;
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

	void Window::ClearKeys()
	{
		memset(m_Keys, 0, MAX_KEYS);
		memset(m_KeyState, 0, MAX_KEYS);
		memset(m_KeyTyped, 0, MAX_KEYS);

		memset(m_MouseButtons, 0, MAX_BUTTONS);
		memset(m_MouseState, 0, MAX_BUTTONS);
		memset(m_MouseClicked, 0, MAX_BUTTONS);
	}
} }
