
#include "Window.h"

#include "al/graphics/TextureManager.h"

#include "al/Types.h"
#include "al/utils/Log.h"
#include "Input.h"

#include "gl/gl.h"
#include <GLFW/glfw3.h>
#include <FreeImage.h>

namespace al {

	using namespace graphics;

	GLFWwindow* Window::s_Instance = nullptr;

	Window::Window(const String& title, WindowProperties properties)
		:m_Title(title), m_Properties(properties)
	{
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


		Window::s_Instance = m_Window;

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

		m_InputManager = new InputManager();
	}

	Window::~Window()
	{
		audio::AudioEngine::Clean();
		TextureManager::Clean();
		glfwTerminate();
	}

	void Window::SetVsync(bool enabled)
	{
		m_Properties.vsync = enabled; 
		glfwSwapInterval(enabled); 
	}

	//	bool Window::IsKeyTyped(unsigned keycode) const
	//	{
	//		if (keycode >= MAX_KEYS)
	//		{
	//			AL_WARN("[Input] Keycode '", keycode, "' is out of range!");
	//			return false;
	//		}
	//
	//		return m_KeyTyped[keycode];
	//	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

 	void Window::Update()
	{
		GLErrorCheck();
		
		m_InputManager->Update();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

		audio::AudioEngine::Update();
	}

	bool Window::Closed()
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::SetTitle(const String& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void InputManager::SetMousePosition(const glm::vec2& position)
	{
		glfwSetCursorPos(Window::GetCallback(), position.x, position.y);
	}

	void InputManager::SetMouseCursor(int32 cursor)
	{
		if (cursor == AL_NO_CURSOR)
		{
			if (IsMouseGrabbed())
				glfwSetInputMode(Window::GetCallback(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(Window::GetCallback(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
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
		win->m_InputManager->m_KeyState[key] = action != GLFW_PRESS;
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_InputManager->m_MouseButtons[button] = action != GLFW_PRESS;
	}

	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_InputManager->m_MousePosition = { xpos, ypos };
	}

}
