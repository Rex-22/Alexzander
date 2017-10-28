#include "Window.h"

#include <GLFW/glfw3.h>

#include "al/utils/Timer.h"
#include "al/Types.h"

#include "gl/gl.h"

namespace al { namespace graphics {

	Window::Window(const char *title, int width, int height, const app::Application* app)
	{
		m_App = app;
		m_Title = title;
		m_Width = width;
		m_Height = height;

		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_Keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
		}

		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW window!" << std::endl;
		}

		const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xp = (vidmode->width - width) / 2;
		int yp = (vidmode->height - height) / 2;

		glfwSetWindowPos(m_Window, xp, yp);

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);

		glfwSwapInterval(0.0);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Could not initialize GLEW!" << std::endl;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	}

	Window::~Window()
	{
		delete m_App;
		glfwTerminate();
	}

	void Window::Show() const
	{
		glfwShowWindow(m_Window);
		Timer time;
		float timer = 0;
		uint frames = 0;
		while (!Closed())
		{
			Clear();

			m_App->OnUpdate(time.elapsed());
			m_App->OnRender();

			Update();
			frames++;
			if (time.elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				printf("%d fps\n", frames);
				frames = 0;
			}
		}

		glfwTerminate();
	}

	void Window::GLErrorCheck()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
	}

	bool Window::IsKeyPressed(unsigned int keycode) const
	{
		// TODO: Log this!
		if (keycode >= MAX_KEYS)
			return false;

		return m_Keys[keycode];
	}
	 
	bool Window::IsMouseButtonPressed(unsigned int button) const
	{
		// TODO: Log this!
		if (button >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[button];
	}

	void Window::GetMousePosition(double& x, double& y) const
	{
		x = mx;
		y = my;
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

 	void Window::Update() const
	{
		GLErrorCheck();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool Window::Closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void WindowResizeCallback(GLFWwindow *window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		win->m_Width = width;
		win->m_Height = height;
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

} }