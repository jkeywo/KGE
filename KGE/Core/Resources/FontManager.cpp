#include "KGE.hpp"
#include "Core/Resources/FontManager.hpp"

namespace KGE
{
	FontManager::FontManager()
	{
		m_xFontList.clear();
	}
	FontManager::~FontManager()
	{
		m_xFontList.clear();
	}

	sf::Font* FontManager::LoadFont(const std::string& szFileName)
	{
		Hash xFontHash = Hash(szFileName);
		fontcollection_t::iterator xIt = m_xFontList.find(xFontHash);
		if (xIt != m_xFontList.end())
		{
			xIt->second.second += 1;
			return &(xIt->second.first);
		}
		else
		{
			sf::Font xNewFont;
			if (xNewFont.loadFromFile(szFileName))
			{
				m_xFontList.insert(fontcollectionpair_t(xFontHash, fontpair_t(xNewFont, 1)));
				xIt = m_xFontList.find(xFontHash);
				if (xIt != m_xFontList.end())
				{
					return &(xIt->second.first);
				}
			}
		}
		return NULL;
	}

	sf::Font* FontManager::GetFont(const Hash& xHash)
	{
		fontcollection_t::iterator xIt = m_xFontList.find(xHash);
		if (xIt != m_xFontList.end())
		{
			return &(xIt->second.first);
		}
		return NULL;
	}
	void FontManager::ReleaseFont(const Hash& xHash)
	{
		fontcollection_t::iterator xIt = m_xFontList.find(xHash);
		if (xIt != m_xFontList.end())
		{
			xIt->second.second -= 1;
			if( xIt->second.second < 1 )
			{
				m_xFontList.erase(xIt);
			}
		}
	}

	void FontManager::ReleaseFont(sf::Font* pxFont)
	{
		for (fontcollection_t::iterator xIt(m_xFontList.begin()); xIt != m_xFontList.end(); xIt++)
		{
			if (&xIt->second.first == pxFont)
			{
				xIt->second.second -= 1;
				if( xIt->second.second < 1 )
				{
					m_xFontList.erase(xIt);
				}
				return;
			}
		}
	}
};