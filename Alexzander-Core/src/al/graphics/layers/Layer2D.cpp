#include "al/al.h"
#include "Layer2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "al/scene/Scene2D.h"

namespace al { namespace graphics {
	
	Layer2D::Layer2D(const glm::mat4& projecton)
	{
		m_Scene = new Scene2D(projecton);
		m_Renderer = m_Scene->GetRenderer();
		m_Renderer->SetCamera(m_Scene->GetCamera());
	}

	Layer2D::Layer2D(Scene2D* scene)
		:m_Scene(scene)
	{
		m_Renderer = new Renderer2D();
		m_Renderer->SetCamera(m_Scene->GetCamera());
	}


	Layer2D::~Layer2D()
	{
		delete m_Scene;

		for (int i = 0; i < m_Renderables.size(); ++i)
			delete m_Renderables[i];
	}

	void Layer2D::Init()
	{
		OnInit(*m_Renderer);
	}

	void Layer2D::OnInit(Renderer2D& renderer)
	{
		
	}


	Sprite* Layer2D::Add(Sprite* sprite)
	{
		m_Scene->Add(new entity::Entity(sprite, glm::translate(glm::mat4(1.0f), sprite->GetPosition())));
		return sprite;
	}

	entity::Entity* Layer2D::Add(entity::Entity* entity)
	{
		m_Scene->Add(entity);
		return entity;
	}

	Renderable2D* Layer2D::Submit(Renderable2D* renderable)
	{
		m_Renderables.push_back(renderable);
		return renderable;
	}

	void Layer2D::OnRender()
	{
		m_Scene->OnRender();
		
		m_Renderer->Begin();

		for (const Renderable2D* renderable: m_Renderables)
			renderable->Submit(m_Renderer);	
		
		m_Renderer->End();
		m_Renderer->Flush();

		OnRender(*m_Renderer);

		//TODO(Ruben): Maby this should happen?
		//m_Renderables.clear();
	}

	void Layer2D::OnRender(Renderer2D& renderer)
	{
		
	}

	void Layer2D::OnUpdateInternal(const Timestep& ts)
	{
		OnUpdate(ts);
	}


} }
