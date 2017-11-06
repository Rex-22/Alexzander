#pragma once

#include "al/Common.h"
#include "al/utils/Log.h"

namespace al { namespace graphics {
	
	class AL_API Renderer
	{
	public:
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
	};

} }