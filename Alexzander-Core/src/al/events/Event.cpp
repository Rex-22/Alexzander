#include "al/al.h"
#include "Event.h"

namespace al { namespace events {


	Event::Event(Type type)
		:m_Type(type), m_Handled(false)
	{}

	String Event::ToString() const
	{
		return "Event: ";
	}

	String Event::TypeToString(Type type)
	{
		switch (type)
		{
		case Type::MOUSE_PRESSED:
			return "MOUSE_PRESSED";
		case Type::MOUSE_RELEASED:
			return "MOUSE_RELEASED";
		case Type::MOUSE_MOVED:
			return "MOUSE_MOVED";
		case Type::KEY_PRESSED:
			return "KEY_PRESSED";
		case Type::KEY_RELEASED:
			return "KEY_RELEASED";
		case Type::WINDOW_RESIZE:
			return "WINDOW_RESIZE";
		case Type::UNKNOWN:
			return "UNKNOWN";
		default:
			return "UNKNOWN";
		}
	}


} }