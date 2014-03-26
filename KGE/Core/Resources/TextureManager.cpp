#include "KGE.hpp"
#include "Core/Resources/TextureManager.hpp"

namespace KGE
{
	TextureManager::TextureManager()
	{
		m_xTextureList.clear();
	}
	TextureManager::~TextureManager()
	{
		m_xTextureList.clear();
	}

	sf::Texture* TextureManager::LoadTexture( const std::string& szFileName )
	{
		return LoadTextureWithAlias( szFileName, Hash(szFileName) );
	}
	sf::Texture* TextureManager::LoadTextureWithAlias( const std::string& szFileName, const Hash& xAlias )
	{
		texturecollection_t::iterator xIt = m_xTextureList.find( xAlias );
		if( xIt != m_xTextureList.end() )
		{
			xIt->second.second += 1;
			return &(xIt->second.first);
		}
		else
		{
			sf::Texture xNewTexture;
			if( xNewTexture.loadFromFile(szFileName) )
			{
				m_xTextureList.insert( texturecollectionpair_t( xAlias, texturepair_t( xNewTexture, 1 ) )  );
				xIt = m_xTextureList.find( xAlias );
				if( xIt != m_xTextureList.end() )
				{
					return &(xIt->second.first);
				}
			}
		}
		return NULL;
	}

	sf::Texture* TextureManager::GetTexture( const Hash& xHash )
	{
		texturecollection_t::iterator xIt = m_xTextureList.find( xHash );
		if( xIt != m_xTextureList.end() )
		{
			return &(xIt->second.first);
		}
		return NULL;
	}
	void TextureManager::ReleaseTexture( const Hash& xHash )
	{
		texturecollection_t::iterator xIt = m_xTextureList.find( xHash );
		if( xIt != m_xTextureList.end() )
		{
			xIt->second.second -= 1;
			if( xIt->second.second < 1 )
			{
				m_xTextureList.erase( xIt );
			}
		}
	}

	void TextureManager::ReleaseTexture( sf::Texture* pxTexture )
	{
		for( texturecollection_t::iterator xIt(m_xTextureList.begin()); xIt != m_xTextureList.end(); xIt++ )
		{
			if( &xIt->second.first == pxTexture )
			{
				xIt->second.second -= 1;
				if( xIt->second.second < 1 )
				{
					m_xTextureList.erase( xIt );
				}
				return;
			}
		}
	}
};