#ifndef STELLAR_MUSIC_HANDLER_H
#define STELLAR_MUSIC_HANDLER_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class MusicHandler
	{
	public:
		void Play(const std::filesystem::path& _path, bool _loop, sf::Time _offset = sf::Time::Zero);
		void UpdateVolume();
		void StopMusic();

		inline sf::Music& GetMusic() { return *instance->currentMusic; }

		// Get the instance of MusicHandler.
		static MusicHandler& Get();
		static void Shutdown();

	private:
		sf::Music* currentMusic = nullptr;
		std::filesystem::path musicPath;
		inline static MusicHandler* instance;
	};
}
#endif