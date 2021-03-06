#pragma once

#include "al/Common.h"
#include "al/app/Window.h"
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

		virtual void Init();
		virtual void OnTick();
		virtual void OnUpdateInternal(const Timestep& ts);
		virtual void OnUpdate(const Timestep& ts);
		virtual void OnEvent(events::Event& event);
		virtual void OnRender();
		
		virtual void Clean();
	public:
		virtual bool OnResize(uint width, uint height) { return false; }
	};

} }
