#ifndef STELLAR_CONTROLLER_INPUT_H
#define STELLAR_CONTROLLER_INPUT_H

#include "Stellar/Core/Common.h"

namespace Stellar
{
	enum class ControllerButton
	{
		UNKNOWN,
		FACE_DOWN,
		FACE_RIGHT,
		FACE_LEFT,
		FACE_UP,
		L1,
		R1,
		L3,
		R3,
		SELECT,
		START,
		HOME
	};

	enum class ControllerAxis
	{
		UNKNOWN,
		L_HOR,
		L_VER,
		R_HOR,
		R_VER,
		L2,
		R2,
		DPAD_HOR,
		DPAD_VER
	};

	class ControllerInput
	{
	public:
		ControllerInput() = delete;

		static bool IsConnected(unsigned int _slot = 0);
		static bool IsPlayStation(unsigned int _slot = 0);
		static bool IsPressed(ControllerButton _button, unsigned int _slot = 0);
		static float GetAxisValue(ControllerAxis _axis, unsigned int _slot = 0);

		// Converts a SFML Button to a ControllerButton
		static ControllerButton GetButton(unsigned int _button, unsigned int _slot = 0);

		// Converts a SFML Axis to a ControllerAxis
		static ControllerAxis GetAxis(unsigned int _axis, unsigned int _slot = 0);

		// Converts a ControllerButton to a SFML Button
		static int GetSFMLButton(ControllerButton _button, unsigned int _slot = 0);

		// Converts a ControllerAxis to a SFML Axis
		static int GetSFMLAxis(ControllerAxis _axis, unsigned int _slot = 0);

		static inline bool IsUsed() { return isUsed; }
		static inline void SetUsed(bool _used) { isUsed = _used; }

	private:
		static bool isUsed;
	};
}

#endif