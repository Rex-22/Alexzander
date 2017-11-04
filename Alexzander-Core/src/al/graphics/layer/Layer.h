#pragma once

#include "al/Common.h"
#include "al/graphics/Window.h"
#include "al/utils/Timestep.h"

namespace al { namespace graphics {
	class AL_API Layer
	{
	protected:
		Window* m_Window;
		bool m_Visible;
	public:
		Layer();
		virtual ~Layer() {}

		inline bool IsVisible() const { return m_Visible; }
		inline void SetVisible(bool visible) { m_Visible = visible; }

		virtual void OnInit();
		virtual void OnRender();
		virtual void OnUpdate(const Timestep& ts);
		virtual void OnTick();
		
		virtual void Clean();
		inline void SetWindow(Window* window) { m_Window = window; }
	};

} }
