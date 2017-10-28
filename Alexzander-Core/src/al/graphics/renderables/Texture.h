#pragma once

#include "al/Common.h"
#include "al/Types.h"
#include "gl/gl.h"

namespace al { namespace graphics {
	
	class AL_API Texture
	{
	private :
		String m_FilePath;
		GLuint m_ID;
		uint m_Width, m_Height;
	public:
		Texture(const String& path);
		~Texture();
		void Bind() const;
		void Unbind() const;

		inline const uint GetWidth() const { return m_Width; }
		inline const uint GetHeight() const { return m_Height; }
		inline const GLuint GetID() const { return m_ID; }
	private:
		GLuint Load();
	};

} }
