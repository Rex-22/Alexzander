#include "al/al.h"

#ifdef AL_PLATFORM_GLFW

#ifdef AL_PLATFORM_WINDOWS
	#error Multiple platforms spesified
#endif

#include "al/app/Window.h"
#include "al/graphics/renderer/IRenderer.h"

#include <GLFW/glfw3.h>
#include "al/events/WindowEvent.h"

namespace al {

#define MOUSE_MOVE -1
#define MOUSE_RELEASE -2

	void GLFWWindowResizeCallback(GLFWwindow *window, int width, int height);
	void GLFWFramebufferSizeCallback(GLFWwindow *window, int width, int height);
	void GLFWFocusCallback(GLFWwindow *window, int focused);
	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	using namespace events;
	using namespace graphics;

	extern void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y);
	extern void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message);

	GLFWwindow* window;

	bool Window::PlatformInit()
	{
		if (!glfwInit())
		{
			AL_ERROR("[Engine] Failed to initialize GLFW!");
			return false;
		}

		window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Title.c_str(), NULL, NULL);
		if (window == NULL)
		{
			AL_ERROR("[Engine] Failed to create GLFW window!");
			return false;
		}

		RegisterWindowClass(window, this);

		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xp = (vidmode->width - m_Properties.width) / 2;
		int yp = (vidmode->height - m_Properties.height) / 2;

		glfwSetWindowPos(window, xp, yp);

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);

		glfwSetWindowSizeCallback(window, GLFWWindowResizeCallback);
		glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
		glfwSetWindowFocusCallback(window, GLFWFocusCallback);
		glfwSetKeyCallback(window, GLFWKeyCallback);
		glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);

		glfwSwapInterval(m_Properties.vsync);

		glfwShowWindow(window);

		return true;
	}

	void Window::PlatformUpdate()
	{
		if(glfwWindowShouldClose(window))
		{
			m_Closed = true;
			return;
		}

		m_InputManager->PlatformUpdate();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Window::SetVsync(bool enabled)
	{
		m_Properties.vsync = enabled;
		glfwSwapInterval(enabled);
	}

	void Window::SetTitle(const String& title)
	{
		m_Title = title;
		glfwSetWindowTitle(window, title.c_str());
	}

	void ResizeCallback(Window* window, int32 width, int32 height)
	{
		window->m_Properties.width = width;
		window->m_Properties.height = height;
		//FontManager::SetScale(maths::vec2(window->m_Properties.width / 32.0f, window->m_Properties.height / 18.0f));

		if (window->m_EventCallback)
			window->m_EventCallback(ResizeWindowEvent((uint)width, (uint)height));
	}

	void FocusCallback(Window* window, bool focused)
	{
		if (!focused)
		{
			window->m_InputManager->ClearKeys();
			window->m_InputManager->ClearMouseButtons();
		}
	}

	void GLFWWindowResizeCallback(GLFWwindow *window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		ResizeCallback(win, width, height);
	}

	void GLFWFocusCallback(GLFWwindow* window, int focused)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		FocusCallback(win, focused);
	}

	void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Renderer::FrameBufferResize(width, height);
	}

	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		static int prv_action = action;
		Window* win = Window::GetWindowClass(window);
		if (action == GLFW_REPEAT)
				KeyCallback(win->GetInputManager(), GLFW_REPEAT, key, prv_action);
		else
		{
			prv_action = action;
			KeyCallback(win->GetInputManager(), action, key, action);
		}
	}

	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
			MouseButtonCallback(win->GetInputManager(), button, win->GetInputManager()->GetMousePosition().x, win->GetInputManager()->GetMousePosition().y);
		else if (action == GLFW_RELEASE)
			MouseButtonCallback(win->GetInputManager(), MOUSE_RELEASE, win->GetInputManager()->GetMousePosition().x, win->GetInputManager()->GetMousePosition().y);
	}

}

#endif