#include "al/al.h"

#include "al/app/Input.h"
#include "al/utils/Log.h"

namespace al {

	InputManager* Input::s_InputManager = nullptr;

	InputManager::InputManager()
		:m_MouseGrabbed(false)
	{
		ClearKeys();
		ClearMouseButtons();

		Input::s_InputManager = this;
	}

	void InputManager::Update()
	{
		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_LastKeyState, m_KeyState, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	void InputManager::ClearKeys()
	{
		for (int32 i = 0; i < MAX_KEYS; i++)
		{
			m_KeyState[i] = false;
			m_LastKeyState[i] = false;
		}
		m_KeyModifiers = 0;
	}

	void InputManager::ClearMouseButtons()
	{
		for (int32 i = 0; i < MAX_BUTTONS; i++)
		{
			m_MouseButtons[i] = false;
			m_MouseState[i] = false;
			m_MouseClicked[i] = false;
		}
	}

	bool InputManager::IsKeyPressed(uint keycode) const
	{
		if (keycode >= MAX_KEYS)
		{
			AL_WARN("[Input] Keycode '", keycode, "' is out of range!");
			return false;
		}

		return m_KeyState[keycode];
	}


	bool InputManager::IsMouseButtonPressed(uint button) const
	{
		if (button >= MAX_BUTTONS)
		{
			AL_WARN("[Input] Mouse button '", button, "' is out of range!");
			return false;
		}

		return m_MouseButtons[button];
	}

	bool InputManager::IsMouseClicked(uint button) const
	{
		if (button >= MAX_BUTTONS)
		{
			AL_WARN("[Input] Mouse button '", button, "' is out of range!");
			return false;
		}

		return m_MouseClicked[button];
	}

	const glm::vec2& InputManager::GetMousePosition() const
	{
		return m_MousePosition;
	}

	const bool InputManager::IsMouseGrabbed() const
	{
		return m_MouseGrabbed;
	}

	void InputManager::SetMouseGrabbed(bool grabbed)
	{
		m_MouseGrabbed = grabbed;
	}
		

}