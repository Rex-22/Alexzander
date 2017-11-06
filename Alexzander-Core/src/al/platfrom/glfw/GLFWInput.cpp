#include "al/al.h"
#include "al/app/Input.h"
#include "al/utils/Log.h"

#include <GLFW/glfw3.h>

#include "al/app/Window.h"
#include "al/events/Events.h"

namespace al {
	
	using namespace events;

	extern GLFWwindow* window;

	void InputManager::PlatformUpdate()
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		glm::vec2 mousePos = glm::vec2((float)xpos, (float)ypos);
		if (mousePos != m_MousePosition)
		{
			m_EventCallback(MouseMovedEvent(mousePos.x, mousePos.y, m_MouseButtons[AL_MOUSE_LEFT]));
			m_MousePosition = mousePos;
		}
	}

	void InputManager::SetMousePosition(const glm::vec2& position)
	{
		glfwSetCursorPos(window, position.x, position.y);
	}
	
	void InputManager::SetMouseCursor(int32 cursor)
	{
		if (cursor == AL_NO_CURSOR)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void KeyCallback(InputManager* inputManager, int32 flags, int32 key, uint message)
	{
		bool pressed = message == GLFW_PRESS && message != GLFW_RELEASE;
		inputManager->m_KeyState[key] = pressed;

		bool repeat = flags == GLFW_REPEAT;

		switch (key)
		{
		case GLFW_KEY_UP:
			key = AL_KEY_UP;
			break;
		case GLFW_KEY_DOWN:
			key = AL_KEY_DOWN;
			break;
		case GLFW_KEY_LEFT:
			key = AL_KEY_LEFT;
			break;
		case GLFW_KEY_RIGHT:
			key = AL_KEY_RIGHT; 
			break;
		}

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
		{
			inputManager->m_EventCallback(events::KeyPressedEvent(key, repeat, inputManager->m_KeyModifiers));
		}
		else
			inputManager->m_EventCallback(events::KeyReleasedEvent(key));
	}

	void MouseButtonCallback(InputManager* inputManager, int32 button, int32 x, int32 y)
	{
		bool down = false;

		static int32 last_button = button;

		if (button == -1)
		{
			button = 32;
			down = true;
		}
		else if (button == -2)
		{
			button = last_button;
			down = false;
		}
		else
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

}
