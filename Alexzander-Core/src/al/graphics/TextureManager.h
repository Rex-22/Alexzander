#pragma once

#include "al/al.h"
#include "al/Common.h"
#include "al/graphics/Texture.h"
namespace al { namespace graphics {

	class AL_API TextureManager
	{
	private:
		static std::vector<Texture*> m_Textures;
	public:
		static void Add(Texture* texture);
		static Texture* Get(const std::string& name);
		static void Clean();
	private:
		TextureManager() {}
	};

} }

