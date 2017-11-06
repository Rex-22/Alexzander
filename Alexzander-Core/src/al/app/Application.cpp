#include "Application.h"

#include "al/graphics/layer/Layer.h"

namespace al { 
	
	using namespace graphics;

	Application* Application::s_Instance = nullptr;

	void Application::Init()
	{
		PlatformInit();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.push_back(layer);
		layer->OnInit();
	}

	Layer* Application::PopLayer()
	{
		Layer* layer = m_LayerStack.back();
		m_LayerStack.pop_back();
		return layer;
	}

	Layer* Application::PopLayer(Layer* layer)
	{
		for (uint i = 0; i < m_LayerStack.size(); i++)
		{
			if (m_LayerStack[i] == layer)
			{
				m_LayerStack.erase(m_LayerStack.begin() + i);
				break;
			}
		}
		return layer;
	}


	void Application::PushOverlay(Layer* layer)
	{
		m_OverlayStack.push_back(layer);
		layer->OnInit();
	}

	Layer* Application::PopOverlay()
	{
		Layer* layer = m_OverlayStack.back();
		m_OverlayStack.pop_back();
		return layer;
	}

	Layer* Application::PopOverlay(Layer* layer)
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
		{
			if (m_OverlayStack[i] == layer)
			{
				m_OverlayStack.erase(m_OverlayStack.begin() + i);
				break;
			}
		}
		return layer;
	}

	void Application::OnTick()
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->OnTick();

		for (uint i = 0; i < m_LayerStack.size(); i++)
			m_LayerStack[i]->OnTick();
	}

	void Application::OnUpdate(const Timestep& ts)
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->OnUpdate(ts);

		for (uint i = 0; i < m_LayerStack.size(); i++)
			m_LayerStack[i]->OnUpdate(ts);
	}

	void Application::OnRender()
	{
		for (uint i = 0; i < m_LayerStack.size(); i++)
		{
			if (m_LayerStack[i]->IsVisible())
				m_LayerStack[i]->OnRender();
		}

		for (uint i = 0; i < m_OverlayStack.size(); i++)
		{
			if (m_OverlayStack[i]->IsVisible())
				m_OverlayStack[i]->OnRender();
		}
	} 

	void Application::OnEvent(events::Event& event)
	{
		if (event.IsHandled())
			return;

		for (int32 i = m_OverlayStack.size() - 1; i >= 0; i--)
		{
			m_OverlayStack[i]->OnEvent(event);
			if (event.IsHandled())
				return;
		}

		for (int32 i = m_LayerStack.size() - 1; i >= 0; i--)
		{
			m_LayerStack[i]->OnEvent(event);
			if (event.IsHandled())
				return;
		}
	}
}