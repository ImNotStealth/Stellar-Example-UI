#ifndef STELLAR_ASSET_MANAGER_H
#define STELLAR_ASSET_MANAGER_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class AssetManager
	{
	public:
		static sf::Texture& GetTexture(const std::filesystem::path& _filePath);
		static sf::Font& GetFont(const std::filesystem::path& _filePath);
		static sf::SoundBuffer& GetSoundBuffer(const std::filesystem::path& _filePath);
		static sf::Music& GetMusic(const std::filesystem::path& _filePath);

		static void Shutdown();

	private:
		static AssetManager& Get();

	private:
		std::map<std::filesystem::path, sf::Texture> textureMap;
		std::map<std::filesystem::path, std::shared_ptr<sf::Font>> fontMap;
		std::map<std::filesystem::path, sf::SoundBuffer> soundBufferMap;
		std::map<std::filesystem::path, std::unique_ptr<sf::Music>> musicMap;

		sf::Texture textureError;

		inline static AssetManager* instance = nullptr;
	};
}

#endif