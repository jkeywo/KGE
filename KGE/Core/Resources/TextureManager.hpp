#pragma once

namespace KGE
{
	class TextureManager
	{
		typedef std::pair< sf::Texture, u32 > texturepair_t;
		typedef std::pair< Hash, texturepair_t > texturecollectionpair_t;
		typedef std::map< Hash, texturepair_t > texturecollection_t;
	public:
		static TextureManager& Get() { static TextureManager xSingleton; return xSingleton; }

		TextureManager();
		~TextureManager();

		sf::Texture* LoadTexture( const std::string& szFileName );
		sf::Texture* LoadTextureWithAlias( const std::string& szFileName, const Hash& xAlias );

		sf::Texture* GetTexture( const Hash& xHash );
		void ReleaseTexture( const Hash& xHash );
		void ReleaseTexture( sf::Texture* pxTexture );

	protected:
		texturecollection_t m_xTextureList;
	};
};