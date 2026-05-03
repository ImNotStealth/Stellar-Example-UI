#ifndef STELLAR_SOUND_HANDLER_H
#define STELLAR_SOUND_HANDLER_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	enum class SoundType
	{
		NONE,
		UI,
		SFX
	};

	class SoundHandler
	{
	public:
		void Play(const std::filesystem::path& _path, SoundType _type = SoundType::NONE, float _pitch = 1.f);

		void Update(float _deltaTime);

		void PauseAll();
		void UnpauseAll();
		void ClearAll();

		// Get the instance of SoundHandler.
		static SoundHandler& Get();
		static void Shutdown();

	private:
		std::vector<std::shared_ptr<sf::Sound>> sounds;
		float updateTimer = 0.f;
		inline static SoundHandler* instance = nullptr;
	};
}

#endif