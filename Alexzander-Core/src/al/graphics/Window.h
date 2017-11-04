#pragma once

#include <iostream>
#include <functional>

#include "al/Common.h"
#include "al/graphics/FontManager.h"

#include "al/audio/AudioEngine.h"

struct GLFWwindow;

namespace al { namespace graphics {
	
#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	struct AL_API WindowProperties
	{
		int width, height;
		bool vsync;
	};

	class AL_API Window
	{
	private:
		String m_Title;
		WindowProperties m_Properties;
		GLFWwindow *m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];

		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		double mx, my;

	public:
		Window(const String& name, WindowProperties properties);
		~Window();
		inline GLFWwindow* GetCallback() const { return m_Window; }

		static void Clear();
		void Update();
		void UpdateInput();
		bool Closed();

		inline int GetWidth() const { return m_Properties.width; }
		inline int GetHeight() const { return m_Properties.height; }

		inline bool IsVsyncEnabled() const { return m_Properties.vsync; }
		void SetVsync(bool enabled);

		bool IsKeyPressed(unsigned int keycode) const;
		bool IsKeyTyped(unsigned int keycode) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		bool IsMouseClicked(unsigned int button) const;
		glm::vec2 GetMousePosition() const;

		void ClearKeys();
	private:
		
		friend static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		friend static void WindowResizeCallback(GLFWwindow *window, int width, int height);
		friend static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

	public:
		static void GLErrorCheck();
	};

} }

#define AL_MOUSE_LEFT	  0x00
#define AL_MOUSE_MIDDLE	  0x01
#define AL_MOUSE_RIGHT    0x02

#define AL_NO_CURSOR	  NULL

#define AL_MODIFIER_LEFT_CONTROL	BIT(0)
#define AL_MODIFIER_LEFT_ALT		BIT(1)
#define AL_MODIFIER_LEFT_SHIFT		BIT(2)
#define AL_MODIFIER_RIGHT_CONTROL	BIT(3)
#define AL_MODIFIER_RIGHT_ALT		BIT(4)
#define AL_MODIFIER_RIGHT_SHIFT		BIT(5)

#define AL_KEY_TAB			  0x09

#define AL_KEY_0			  0x30
#define AL_KEY_1			  0x31
#define AL_KEY_2			  0x32
#define AL_KEY_3			  0x33
#define AL_KEY_4			  0x34
#define AL_KEY_5			  0x35
#define AL_KEY_6			  0x36
#define AL_KEY_7			  0x37
#define AL_KEY_8			  0x38
#define AL_KEY_9			  0x39

#define AL_KEY_A			  0x41
#define AL_KEY_B			  0x42
#define AL_KEY_C			  0x43
#define AL_KEY_D			  0x44
#define AL_KEY_E			  0x45
#define AL_KEY_F			  0x46
#define AL_KEY_G			  0x47
#define AL_KEY_H			  0x48
#define AL_KEY_I			  0x49
#define AL_KEY_J			  0x4A
#define AL_KEY_K			  0x4B
#define AL_KEY_L			  0x4C
#define AL_KEY_M			  0x4D
#define AL_KEY_N			  0x4E
#define AL_KEY_O			  0x4F
#define AL_KEY_P			  0x50
#define AL_KEY_Q			  0x51
#define AL_KEY_R			  0x52
#define AL_KEY_S			  0x53
#define AL_KEY_T			  0x54
#define AL_KEY_U			  0x55
#define AL_KEY_V			  0x56
#define AL_KEY_W			  0x57
#define AL_KEY_X			  0x58
#define AL_KEY_Y			  0x59
#define AL_KEY_Z			  0x5A

#define AL_KEY_LBUTTON        0x01
#define AL_KEY_RBUTTON        0x02
#define AL_KEY_CANCEL         0x03
#define AL_KEY_MBUTTON        0x04

#define AL_KEY_ESCAPE         0x1B
#define AL_KEY_SHIFT          0x10
#define AL_KEY_CONTROL        0x11
#define AL_KEY_MENU           0x12
#define AL_KEY_ALT	          AL_KEY_MENU
#define AL_KEY_PAUSE          0x13
#define AL_KEY_CAPITAL        0x14

#define AL_KEY_SPACE          0x20
#define AL_KEY_PRIOR          0x21
#define AL_KEY_NEXT           0x22
#define AL_KEY_END            0x23
#define AL_KEY_HOME           0x24
#define AL_KEY_RIGHT          262
#define AL_KEY_LEFT           263
#define AL_KEY_DOWN           264
#define AL_KEY_UP             265
#define AL_KEY_SELECT         0x29
#define AL_KEY_PRINT          0x2A
#define AL_KEY_EXECUTE        0x2B
#define AL_KEY_SNAPSHOT       0x2C
#define AL_KEY_INSERT         0x2D
#define AL_KEY_DELETE         0x2E
#define AL_KEY_HELP           0x2F

#define AL_KEY_NUMPAD0        0x60
#define AL_KEY_NUMPAD1        0x61
#define AL_KEY_NUMPAD2        0x62
#define AL_KEY_NUMPAD3        0x63
#define AL_KEY_NUMPAD4        0x64
#define AL_KEY_NUMPAD5        0x65
#define AL_KEY_NUMPAD6        0x66
#define AL_KEY_NUMPAD7        0x67
#define AL_KEY_NUMPAD8        0x68
#define AL_KEY_NUMPAD9        0x69
#define AL_KEY_MULTIPLY       0x6A
#define AL_KEY_ADD            0x6B
#define AL_KEY_SEPARATOR      0x6C
#define AL_KEY_SUBTRACT       0x6D
#define AL_KEY_DECIMAL        0x6E
#define AL_KEY_DIVIDE         0x6F
#define AL_KEY_F1             0x70
#define AL_KEY_F2             0x71
#define AL_KEY_F3             0x72
#define AL_KEY_F4             0x73
#define AL_KEY_F5             0x74
#define AL_KEY_F6             0x75
#define AL_KEY_F7             0x76
#define AL_KEY_F8             0x77
#define AL_KEY_F9             0x78
#define AL_KEY_F10            0x79
#define AL_KEY_F11            0x7A
#define AL_KEY_F12            0x7B
#define AL_KEY_F13            0x7C
#define AL_KEY_F14            0x7D
#define AL_KEY_F15            0x7E
#define AL_KEY_F16            0x7F
#define AL_KEY_F17            0x80
#define AL_KEY_F18            0x81
#define AL_KEY_F19            0x82
#define AL_KEY_F20            0x83
#define AL_KEY_F21            0x84
#define AL_KEY_F22            0x85
#define AL_KEY_F23            0x86
#define AL_KEY_F24            0x87

#define AL_KEY_NUMLOCK        0x90
#define AL_KEY_SCROLL         0x91

#define AL_KEY_LSHIFT         0xA0
#define AL_KEY_RSHIFT         0xA1
#define AL_KEY_LCONTROL       0xA2
#define AL_KEY_RCONTROL       0xA3
#define AL_KEY_LMENU          0xA4
#define AL_KEY_RMENU          0xA5