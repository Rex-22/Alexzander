#pragma once

#include "al/al.h"
#include "al/Common.h"
#include "al/entity//Entity.h"
#include "al/graphics/renderer/Renderer2D.h"
#include "al/graphics/camera/Camera.h"

namespace al {
	
	class AL_API Scene2D
	{
	private:
		graphics::Renderer2D* m_Renderer;
		graphics::Camera* m_Camera;
		std::vector<entity::Entity*> m_Entities;
	public:
		Scene2D();
		Scene2D(const glm::mat4& projectionMatrix);
		~Scene2D();

		void Add(entity::Entity* entity);

		virtual void OnUpdate();
		virtual void OnRender(graphics::Renderer2D& renderer);

		void OnRender();

		inline graphics::Renderer2D* GetRenderer() { return m_Renderer; }
		inline graphics::Camera* const GetCamera() { return m_Camera; }
	};

}
