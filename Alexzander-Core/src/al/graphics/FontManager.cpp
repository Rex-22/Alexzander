#include "FontManager.h"


namespace al { namespace graphics {

	std::vector<Font*> FontManager::m_FontStack;

	FontManager::FontManager(Font* font)
	{
		m_FontStack.push_back(font);
	}


	FontManager::~FontManager()
	{
	}

	void FontManager::Add(Font* font)
	{
		m_FontStack.push_back(font);
	}
	
	Font* FontManager::Get(const String& name)
	{
		for (Font* font : m_FontStack)
		{
			if(font->GetName() == name)
				return font;
		}

		return nullptr;
	}

	void FontManager::Clean()
	{
		for (int i = 0; i < m_FontStack.size(); i++)
			delete m_FontStack[i];
	}
	

} }