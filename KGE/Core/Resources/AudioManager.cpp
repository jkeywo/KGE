#include "KGE.hpp"
#include "Core/Resources/AudioManager.hpp"

namespace KGE
{
	AudioManager::AudioManager()
	{
	}
	AudioManager::~AudioManager()
	{
		FOREACH( xIt, m_xMusicList )
		{
			delete xIt->second.first;	
		}
		m_xMusicList.clear();
		m_xSoundList.clear();
	}

	sf::SoundBuffer* AudioManager::LoadSoundBuffer(const std::string& szFileName)
	{
		Hash xSoundHash = Hash(szFileName);
		soundcollection_t::iterator xIt = m_xSoundList.find(xSoundHash);
		if (xIt != m_xSoundList.end())
		{
			xIt->second.second += 1;
			return &(xIt->second.first);
		}
		else
		{
			sf::SoundBuffer xNewSound;
			if (xNewSound.loadFromFile(szFileName))
			{
				m_xSoundList.insert(soundcollectionpair_t(xSoundHash, soundpair_t(xNewSound, 1)));
				xIt = m_xSoundList.find(xSoundHash);
				if (xIt != m_xSoundList.end())
				{
					return &(xIt->second.first);
				}
			}
		}
		return NULL;
	}

	sf::SoundBuffer* AudioManager::GetSoundBuffer(const Hash& xHash)
	{
		soundcollection_t::iterator xIt = m_xSoundList.find(xHash);
		if (xIt != m_xSoundList.end())
		{
			return &(xIt->second.first);
		}
		return NULL;
	}
	void AudioManager::ReleaseSoundBuffer(const Hash& xHash)
	{
		soundcollection_t::iterator xIt = m_xSoundList.find(xHash);
		if (xIt != m_xSoundList.end())
		{
			xIt->second.second -= 1;
			if( xIt->second.second < 1 )
			{
				m_xSoundList.erase(xIt);
			}
		}
	}

	void AudioManager::ReleaseSoundBuffer(sf::SoundBuffer* pxSoundBuffer)
	{
		for (soundcollection_t::iterator xIt(m_xSoundList.begin()); xIt != m_xSoundList.end(); xIt++)
		{
			if (&xIt->second.first == pxSoundBuffer)
			{
				xIt->second.second -= 1;
				if( xIt->second.second < 1 )
				{
					m_xSoundList.erase(xIt);
				}
				return;
			}
		}
	}

	sf::Music* AudioManager::LoadMusic(const std::string& szFileName)
	{
		Hash xMusicHash = Hash(szFileName);
		musiccollection_t::iterator xIt = m_xMusicList.find(xMusicHash);
		if (xIt != m_xMusicList.end())
		{
			xIt->second.second += 1;
			return xIt->second.first;
		}
		else
		{
			sf::Music* pxNewMusic = new sf::Music();
			if (pxNewMusic && pxNewMusic->openFromFile(szFileName))
			{
				m_xMusicList.insert(musiccollectionpair_t(xMusicHash, musicpair_t(pxNewMusic, 1)));
				xIt = m_xMusicList.find(xMusicHash);
				if (xIt != m_xMusicList.end())
				{
					return xIt->second.first;
				}
			}
		}
		return NULL;
	}

	sf::Music* AudioManager::GetMusic(const Hash& xHash)
	{
		musiccollection_t::iterator xIt = m_xMusicList.find(xHash);
		if (xIt != m_xMusicList.end())
		{
			return xIt->second.first;
		}
		return NULL;
	}
	void AudioManager::ReleaseMusic(const Hash& xHash)
	{
		musiccollection_t::iterator xIt = m_xMusicList.find(xHash);
		if (xIt != m_xMusicList.end())
		{
			xIt->second.second -= 1;
			if( xIt->second.second < 1 )
			{
				delete xIt->second.first;
				m_xMusicList.erase(xIt);
			}
		}
	}

	void AudioManager::ReleaseMusic(sf::Music* pxMusic)
	{
		for (musiccollection_t::iterator xIt(m_xMusicList.begin()); xIt != m_xMusicList.end(); xIt++)
		{
			if (xIt->second.first == pxMusic)
			{
				xIt->second.second -= 1;
				if( xIt->second.second < 1 )
				{
					delete xIt->second.first;
					m_xMusicList.erase(xIt);
				}
				return;
			}
		}
	}
};