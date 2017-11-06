#pragma once

#include "gl/gl.h"
#include "al/graphics/Font.h"

#include "al/Common.h"
#include "al/utils/Log.h"

namespace al { namespace graphics {
	class Renderable;

	class AL_API Renderer
	{
	public:
		virtual ~Renderer() = default;

		static bool Init()
		{
			AL_INFO("[Renderer] Initializing GLEW...");
			if (glewInit() != GLEW_OK)
			{
				AL_ERROR("[Renderer]  Failed to initialize GLEW!");
				return false;
			}

			AL_INFO("[Engine] OpenGL ", glGetString(GL_VERSION));

			//TODO(Ruben): This needs to move...
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;
		}

		static void FrameBufferResize(int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		static void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	private:
		protected:
		std::vector<glm::mat4> m_TransformationStack;

		const glm::mat4* m_LastMatrix;
	protected:
		Renderer()
		{
			m_TransformationStack.push_back(glm::mat4(1.0f));
			m_LastMatrix = &m_TransformationStack.back();
		}
	public:
		void push(glm::mat4 matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else 
				m_TransformationStack.push_back(*m_LastMatrix * matrix);

			m_LastMatrix = &m_TransformationStack.back();
		}

		void pop()
		{
			if (m_TransformationStack.size() > 1)
			{
				m_TransformationStack.pop_back();
				m_LastMatrix = &m_TransformationStack.back();
			}
		}
	public:
		virtual void Begin() {}
		virtual void Submit(const Renderable* renderable) = 0;
		virtual void DrawString(const String& text, float x, float y, Font* font) {};
		virtual void End() {}
		virtual void Flush() = 0;
	};

} } 