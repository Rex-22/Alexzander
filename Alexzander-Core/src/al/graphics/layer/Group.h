#pragma once

#include "al/graphics/renderables/Renderable2D.h"

#include "al/Common.h"

namespace al { namespace graphics {

		class AL_API Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			glm::mat4 m_TransformationMatrix;
		public:
			Group(const glm::mat4& transform);
			~Group();
			void Add(Renderable2D* renderable);
			void Submit(Renderer2D* renderer) const override;
		};

	}
}