#include "MusicHandler.h"

#include "Stellar/Core/AssetManager.h"
#include "Stellar/Core/Settings.h"

namespace Stellar {

	void MusicHandler::Play(const std::filesystem::path& _path, bool _loop, sf::Time _offset)
	{
		if (musicPath.compare(_path) != 0)
		{
			currentMusic = &AssetManager::GetMusic(_path);
			currentMusic->setLoop(_loop);
			UpdateVolume();
			currentMusic->setPlayingOffset(_offset);
			currentMusic->play();
			musicPath = _path;
		}
	}

	void MusicHandler::UpdateVolume()
	{
		if (currentMusic)
		{
			float volume = (float)Settings::Get().volumeMaster * (float)Settings::Get().volumeMusic;
			currentMusic->setVolume(volume / 100.f);
		}
	}

	void MusicHandler::StopMusic()
	{
		musicPath.clear();
		if (currentMusic)
		{
			currentMusic->stop();
		}
	}

	MusicHandler& MusicHandler::Get()
	{
		if (!instance)
		{
			instance = new MusicHandler();
		}

		return *instance;
	}

	void MusicHandler::Shutdown()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
}
