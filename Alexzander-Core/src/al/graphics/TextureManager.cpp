#include "TextureManager.h"

namespace al { namespace graphics {

	std::vector<Texture*> TextureManager::m_Textures;

	void TextureManager::Add(Texture* texture)
	{
		m_Textures.push_back(texture);
	}

	Texture* TextureManager::Get(const std::string& name)
	{
		for (int i = 0; i < m_Textures.size(); ++i)
		{
			if (m_Textures[i]->GetName() == name)
				return m_Textures[i];
		}

		//TODO: Default Texture?
		return nullptr;
	}


	void TextureManager::Clean()
	{
		for (Texture* texture : m_Textures)
			delete texture;
	}



} }
