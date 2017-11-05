#pragma once

#include "al/Common.h"
#include "al/Types.h"

namespace al { namespace events {
	
	

	class AL_API Event
	{
	private:
		friend class EventDispatcher;
	public:
		enum class Type
		{
			MOUSE_PRESSED = BIT(0),
			MOUSE_RELEASED = BIT(1),
			MOUSE_MOVED = BIT(2),

			KEY_PRESSED = BIT(3),
			KEY_RELEASED = BIT(4),

			WINDOW_RESIZE = BIT(6),

			UNKNOWN,
		};
	protected:
		Type m_Type = Type::UNKNOWN;
		bool m_Handled;
	protected:
		Event(Type type);
	public:
		inline Type GetType() const { return m_Type; }
		inline bool IsHandled() const { return m_Handled; }

		virtual String ToString() const;

		static String TypeToString(Type type);
	};

} }