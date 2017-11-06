#pragma once

#include "al/al.h"
#include "al/Common.h"

namespace al { namespace entity {
		class Entity;
} }

namespace al { namespace entity { namespace component {

	struct AL_API ComponentType
	{
		String name;
	};

	class AL_API Component
	{
	protected:
		Entity* m_Entity;
	public:
		virtual Entity* GetEntity() { return m_Entity; }
		virtual ComponentType* GetType() const { return nullptr; }
	};

} } }
