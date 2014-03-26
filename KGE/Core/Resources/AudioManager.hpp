#pragma once

namespace KGE
{
	class AudioManager
	{
		typedef std::pair< sf::SoundBuffer, u32 > soundpair_t;
		typedef std::pair< Hash, soundpair_t > soundcollectionpair_t;
		typedef std::map< Hash, soundpair_t > soundcollection_t;

		typedef std::pair< sf::Music*, u32 > musicpair_t;
		typedef std::pair< Hash, musicpair_t > musiccollectionpair_t;
		typedef std::map< Hash, musicpair_t > musiccollection_t;
	public:
		static AudioManager& Get() { static AudioManager xSingleton; return xSingleton; }

		AudioManager();
		~AudioManager();

		sf::SoundBuffer* LoadSoundBuffer(const std::string& szFileName);
		sf::SoundBuffer* GetSoundBuffer(const Hash& xHash);
		void ReleaseSoundBuffer(const Hash& xHash);
		void ReleaseSoundBuffer(sf::SoundBuffer* pxSoundBuffer);

		sf::Music* LoadMusic(const std::string& szFileName);
		sf::Music* GetMusic(const Hash& xHash);
		void ReleaseMusic(const Hash& xHash);
		void ReleaseMusic(sf::Music* pxMusic);

	protected:
		soundcollection_t m_xSoundList;
		musiccollection_t m_xMusicList;
	};
};