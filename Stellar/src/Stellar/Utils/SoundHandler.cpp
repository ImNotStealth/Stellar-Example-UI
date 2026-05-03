#include "SoundHandler.h"

#include "Stellar/Core/AssetManager.h"
#include "Stellar/Core/Settings.h"

#define SOUND_HANDLER_UPDATE 1.f

namespace Stellar {

	void SoundHandler::Play(const std::filesystem::path& _path, SoundType _type, float _pitch)
	{
		std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();

		sound->setBuffer(AssetManager::GetSoundBuffer(_path));
		float volume = (float)Settings::Get().volumeMaster;
		switch (_type)
		{
		case SoundType::UI:
			volume *= (float)Settings::Get().volumeUI;
			break;
		case SoundType::SFX:
			volume *= (float)Settings::Get().volumeSFX;
			break;
		default:
			std::cout << "Unknown Sound Type: " << (int)_type << ", only applying Master Volume." << std::endl;
			break;
		}
		sound->setPitch(_pitch);
		sound->setVolume(volume / 100.f);
		sound->play();

		sounds.push_back(sound);
	}

	void SoundHandler::Update(float _deltaTime)
	{
		updateTimer += _deltaTime;
		if (updateTimer >= SOUND_HANDLER_UPDATE)
		{
			sounds.erase(std::remove_if(sounds.begin(), sounds.end(),
				[](const std::shared_ptr<sf::Sound>& sound) {
					return sound->getStatus() == sf::Sound::Stopped;
				}),
				sounds.end());
			updateTimer = 0.f;
		}
	}

	void SoundHandler::PauseAll()
	{
		for (const auto& sound : sounds)
		{
			if (sound->getStatus() == sf::Sound::Playing)
			{
				sound->pause();
			}
		}
	}

	void SoundHandler::UnpauseAll()
	{
		for (const auto& sound : sounds)
		{
			if (sound->getStatus() == sf::Sound::Paused)
			{
				sound->play();
			}
		}
	}

	void SoundHandler::ClearAll()
	{
		sounds.clear();
	}

	SoundHandler& SoundHandler::Get()
	{
		if (!instance)
		{
			instance = new SoundHandler();
		}

		return *instance;
	}

	void SoundHandler::Shutdown()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
}