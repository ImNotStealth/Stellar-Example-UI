#ifndef STELLAR_UTILS_H
#define STELLAR_UTILS_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class Utils
	{
	public:
		// Scales the provided value depending on the window size.
		static float Scale(float _value);

		// Sets the system's mouse cursor
		static void SetCursor(sf::Cursor::Type _type);

		static float IsFloatEqual(float _a, float _b, float _tolerance);

		template<typename T>
		static T Clamp(T _value, T _min, T _max)
		{
			return std::min(_max, std::max(_value, _min));
		}
	
		static sf::Sprite LoadSprite(const std::filesystem::path& _path, bool _isCentered);
	};
}

#endif