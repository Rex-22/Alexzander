#include "al/al.h"

#include "Texture.h"

#include <FreeImage.h>

#include "al/app/Window.h"
#include "al/utils/ImageUtils.h"

namespace al { namespace graphics {


	Texture::Texture(const String& name, const String& path)
		:m_FilePath(path), m_Name(name)
	{
		m_ID = Load();
	}

	GLuint Texture::Load()
	{
		BYTE* pixels = ImageUtils::LoadImage(m_FilePath.c_str(), &m_Width, &m_Height);

		GLuint result;

		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] pixels;

		return result;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
} }
