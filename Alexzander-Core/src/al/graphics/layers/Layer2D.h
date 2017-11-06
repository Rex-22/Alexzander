#pragma once

#include "al/graphics/renderer/IRenderer.h"
#include "al/graphics/renderables/Renderable2D.h"

#include "al/Common.h"
#include "Layer.h"
#include "al/scene/Scene2D.h"

namespace al { namespace graphics {
	
	class AL_API Layer2D : public Layer
	{
	protected:
		std::vector<Renderable2D*> m_Renderables;

		Renderer2D* m_Renderer;
		Scene2D* m_Scene;
	public :
		Layer2D(const glm::mat4& projecton);
		Layer2D(Scene2D* scene);
		~Layer2D();

		void Init() override;
		virtual void OnInit(Renderer2D& renderer);

		virtual Sprite* Add(Sprite* sprite);
		virtual entity::Entity* Add(entity::Entity* entity);
		virtual Renderable2D* Submit(Renderable2D* renderable);

		inline Scene2D* GetScene() { return m_Scene; }

		void OnRender() override;
		virtual void OnRender(Renderer2D& renderer);
		void OnUpdateInternal(const Timestep& ts) override;
	};

} }
