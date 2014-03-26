#pragma once

namespace KGE
{
	class FontManager
	{
		typedef std::pair< sf::Font, u32 > fontpair_t;
		typedef std::pair< Hash, fontpair_t > fontcollectionpair_t;
		typedef std::map< Hash, fontpair_t > fontcollection_t;
	public:
		static FontManager& Get() { static FontManager xSingleton; return xSingleton; }

		FontManager();
		~FontManager();

		sf::Font* LoadFont(const std::string& szFileName);
		sf::Font* GetFont(const Hash& xHash);
		void ReleaseFont(const Hash& xHash);
		void ReleaseFont(sf::Font* pxFont);

	protected:
		fontcollection_t m_xFontList;
	};
};