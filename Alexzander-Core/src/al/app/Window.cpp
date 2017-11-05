
#include "Window.h"

#include "al/graphics/TextureManager.h"

#include "al/Types.h"
#include "al/utils/Log.h"
#include "Input.h"

#include "gl/gl.h"
#include <GLFW/glfw3.h>
#include <FreeImage.h>

namespace al {

#define MOUSE_MOVE -1
#define MOUSE_RELEASE -2

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

		glfwSetWindowSizeCallback(m_Window, GLFWWindowResizeCallback);
		glfwSetFramebufferSizeCallback(m_Window, GLFWFramebufferSizeCallback);
		glfwSetWindowFocusCallback(m_Window, GLFWFocusCallback);

		glfwSetKeyCallback(m_Window, GLFWKeyCallback);
		glfwSetMouseButtonCallback(m_Window, GLFWMouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, GLFWCursorPositionCallback);

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

	void Window::SetEventCallback(const WindowEventCallback& callback)
	{
		m_EventCallback = callback;
		m_InputManager->SetEventCallback(m_EventCallback);
	}

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

	void ResizeCallback(Window* window, int32 width, int32 height)
	{
		window->m_Properties.width = width;
		window->m_Properties.height = height;

		if (window->m_EventCallback)
			window->m_EventCallback(events::ResizeWindowEvent((uint)width, (uint)height));
	}

	void FocusCallback(Window* window, bool focused)
	{
		if (!focused)
		{
			window->m_InputManager->ClearKeys();
			window->m_InputManager->ClearMouseButtons();
		}
	}

	void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message)
	{
		bool pressed = message == GLFW_PRESS || message == GLFW_RELEASE;
		inputManager->m_KeyState[key] = pressed;

		bool repeat = flags == GLFW_REPEAT;

		int32 modifier = 0;
		switch (key)
		{
		case AL_KEY_CONTROL:
			modifier = AL_MODIFIER_LEFT_CONTROL;
			break;
		case AL_KEY_ALT:
			modifier = AL_MODIFIER_LEFT_ALT;
			break;
		case AL_KEY_SHIFT:
			modifier = AL_MODIFIER_LEFT_SHIFT;
			break;
		}
		if (pressed)
			inputManager->m_KeyModifiers |= modifier;
		else
			inputManager->m_KeyModifiers &= ~(modifier);

		if (pressed)
			inputManager->m_EventCallback(events::KeyPressedEvent(key, repeat, inputManager->m_KeyModifiers));
		else
			inputManager->m_EventCallback(events::KeyReleasedEvent(key));
	}

	void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y)
	{
		bool down = false;

		static int32 last_button = button;

		if (button == MOUSE_MOVE)
		{
			button = 32;
			down = true;
		}else if (button == MOUSE_RELEASE)
		{
			button = last_button;
			down = false;
		} else
		{
			last_button = button;
		}

		inputManager->m_MouseButtons[button] = down;
		inputManager->m_MousePosition.x = (float)x;
		inputManager->m_MousePosition.y = (float)y;

		AL_ASSERT(inputManager->m_EventCallback);

		if (down)
			inputManager->m_EventCallback(events::MousePressedEvent(button, (float)x, (float)y));
		else
			inputManager->m_EventCallback(events::MouseReleasedEvent(button, (float)x, (float)y));
	}

	void GLFWWindowResizeCallback(GLFWwindow *window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		ResizeCallback(win, width, height);
	}

	void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void GLFWFocusCallback(GLFWwindow* window, int focused)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		FocusCallback(win, focused);
	}

	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		KeyCallback(win->m_InputManager, action , key, action);
	}

	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
			MouseButtonCallback(win->m_InputManager, button, win->m_InputManager->GetMousePosition().x, win->m_InputManager->GetMousePosition().y);
		else if (action == GLFW_RELEASE)
			MouseButtonCallback(win->m_InputManager, MOUSE_RELEASE, win->m_InputManager->GetMousePosition().x, win->m_InputManager->GetMousePosition().y);
	}

	void GLFWCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		MouseButtonCallback(win->m_InputManager, MOUSE_MOVE, xpos, ypos);
	}

}
