#include "al/al.h"
#include "Layer.h"

namespace al { namespace graphics {


	Layer::Layer()
		: m_Window(Window::GetWindowClass(nullptr)), m_Visible(true) 
	{
		
	}

	void Layer::OnInit()
	{
		
	}

	void Layer::OnUpdate(const Timestep& ts)
	{
		
	}

	void Layer::OnEvent(events::Event& event)
	{
//		events::EventDispatcher dispatcher(event);
//		dispatcher.Dispatch<events::ResizeWindowEvent>([this](events::ResizeWindowEvent& e) { return OnResize(e.GetWidth(), e.GetHeight()); });
	}


	void Layer::OnTick()
	{
		
	}

	void Layer::OnRender()
	{
		
	}



	void Layer::Clean()
	{
		
	}

} }