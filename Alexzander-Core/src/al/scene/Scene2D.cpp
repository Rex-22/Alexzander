#include "al/al.h"

#include "Scene2D.h"
#include "al/app/Application.h"
#include "al/entity/Entity.h"
#include "al/entity/component/SpriteComponent.h"
#include "al/entity/component/TransformComponent.h"
#include "al/graphics/camera/Camera.h"
#include "glm/gtc/matrix_transform.inl"

namespace al {
	
	using namespace graphics;

	using namespace entity;
	using namespace component;

	Scene2D::Scene2D()
	{
		float width = Application::GetApplication().GetWindowWidth();
		float height = Application::GetApplication().GetWindowHeight();
		float aspect = width / height;

		m_Camera = new Camera(glm::ortho(-10.0f * aspect, 10.0f * aspect, -10.0f, 10.0f, -1.0f, 1.0f));
		m_Renderer = new Renderer2D();
		m_Renderer->SetCamera(m_Camera);
	}

	Scene2D::Scene2D(const glm::mat4& projectionMatrix)
		:m_Camera(new Camera(projectionMatrix))
	{
		m_Renderer = new Renderer2D();
		m_Renderer->SetCamera(m_Camera);
	}

	Scene2D::~Scene2D()
	{
		delete m_Camera;
	}

	void Scene2D::Add(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void Scene2D::OnUpdate()
	{

	}

	void Scene2D::OnRender(Renderer2D& renderer)
	{

	}

	void Scene2D::OnRender()
	{
		Camera* camera = m_Camera;

		m_Renderer->Begin();
		for (uint i = 0; i < m_Entities.size(); i++)
		{
			Entity* entity = m_Entities[i];
			SpriteComponent* sprite = entity->GetComponent<SpriteComponent>();
			if (sprite)
			{
				TransformComponent* tc = entity->GetComponent<TransformComponent>();
				AL_ASSERT(tc, "Sprite does not have transform!"); // Sprites MUST have transforms
				sprite->GetSprite()->Submit(m_Renderer);
			}

		}
		OnRender(*m_Renderer);

		m_Renderer->End();
		m_Renderer->Flush();
	}

}
