#ifndef STELLAR_GAME_STATE_SPLASH_CPP
#define STELLAR_GAME_STATE_SPLASH_CPP

#include "GameSplash.h"

#include "Stellar/Core/Game.h"
#include "Stellar/Core/AssetManager.h"

namespace Stellar {

	template<typename T>
	GameSplash<T>::GameSplash()
		: GameState("SplashScreen"), splashCount(0) {}

	template<typename T>
	void GameSplash<T>::Load()
	{
		sf::Vector2u winSize = Settings::GetWindowSize();

		splashCount = 0;

		if (!std::filesystem::exists("Assets/Splash"))
		{
			std::cout << "No Splash textures found, skipping to next GameState." << std::endl;
			Game::Get().SetState<T>();
			return;
		}

		std::vector<std::filesystem::path> files;
		for (const auto& entry : std::filesystem::directory_iterator("Assets/Splash"))
		{
			if (std::filesystem::is_directory(entry))
				continue;

			try
			{
				int i = std::stoi(entry.path().stem().string());
			}
			catch (const std::invalid_argument&)
			{
				continue;
			}

			files.push_back(entry);
		}
		std::sort(files.begin(), files.end(), [](const std::filesystem::path& a, const std::filesystem::path& b)
		{
			return std::stoi(a.stem().string()) < std::stoi(b.stem().string());
		});

		for (const auto& file : files)
		{
			sf::Sprite sprite = {};
			std::string spritePath = std::format("Splash/{}", file.filename().string());
			sprite.setTexture(AssetManager::GetTexture(spritePath));

			sf::Vector2u texSize = sprite.getTexture()->getSize();
			sprite.setOrigin({ (float)texSize.x / 2.f, (float)texSize.y / 2.f });
			sprite.setColor(sf::Color::Transparent);

			ScaleSprite(sprite, texSize, winSize);
			sprite.setPosition({ (float)winSize.x / 2.f, (float)winSize.y / 2.f });

			sprites.push_back(sprite);
		}

		easingFadeIn = Easing(EasingType::IN_CUBIC, 2.f, 0.f, 255.f);
		easingFadeOut = Easing(EasingType::IN_CUBIC, 2.f, 255.f, 0.f);
	}

	template<typename T>
	void GameSplash<T>::OnResize(sf::Vector2u _size)
	{
		for (sf::Sprite& sprite : sprites)
		{
			sf::Vector2u texSize = sprite.getTexture()->getSize();
			ScaleSprite(sprite, texSize, _size);
			sprite.setPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f });
		}
	}

	template<typename T>
	void GameSplash<T>::OnEvent(sf::Event _event)
	{
		if (_event.type == sf::Event::KeyPressed || _event.type == sf::Event::JoystickButtonPressed)
		{
			NextSplash();
		}
	}

	template<typename T>
	void GameSplash<T>::Update(float _deltaTime)
	{
		if (!easingFadeIn.IsFinished())
		{
			easingFadeIn.Update(_deltaTime);
			sprites[splashCount].setColor(sf::Color(255, 255, 255, (int)easingFadeIn.value));
		}
		else if (!easingFadeOut.IsFinished())
		{
			easingFadeOut.Update(_deltaTime);
			sprites[splashCount].setColor(sf::Color(255, 255, 255, (int)easingFadeOut.value));
		}
		else
		{
			NextSplash();
		}
	}

	template<typename T>
	void GameSplash<T>::Draw(sf::RenderTexture& _texture)
	{
		if (splashCount >= sprites.size())
			return;

		_texture.draw(sprites[splashCount]);
	}

	template<typename T>
	void GameSplash<T>::NextSplash()
	{
		splashCount++;
		easingFadeIn.Reset();
		easingFadeOut.Reset();

		if (splashCount >= sprites.size())
			Game::Get().SetState<T>();
	}

	template<typename T>
	void GameSplash<T>::ScaleSprite(sf::Sprite& _sprite, sf::Vector2u& _textureSize, sf::Vector2u& _windowSize)
	{
		float aspectRatio = 16.f / 9.f;
		int hudWidth = _textureSize.x;
		int hudHeight = (int)(hudWidth / aspectRatio);

		if (hudWidth > (int)_windowSize.x)
		{
			hudWidth = _windowSize.x;
			hudHeight = (int)(hudWidth / aspectRatio);
		}

		if (hudHeight > (int)_windowSize.y)
		{
			hudHeight = _windowSize.y;
			hudWidth = (int)(hudHeight * aspectRatio);
		}

		float scaleX = (float)hudWidth / (float)_textureSize.x;
		float scaleY = (float)hudHeight / (float)_textureSize.y;

		_sprite.setScale({ scaleX, scaleY });
	}
}

#endif