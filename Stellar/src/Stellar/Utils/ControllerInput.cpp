#include "ControllerInput.h"

#include "Stellar/Core/Settings.h"

#define PS_VID 1356			// Playstation Vendor ID
#define PS_FACE_DOWN 1		// X
#define PS_FACE_RIGHT 2		// O
#define PS_FACE_LEFT 0		// Square
#define PS_FACE_UP 3		// Triangle
#define PS_L1 4				// L1
#define PS_R1 5				// R1
#define PS_L3 10			// L3
#define PS_R3 11			// R3
#define PS_SHARE 8			// Share
#define PS_START 9			// Start
#define PS_HOME 12			// PS
#define PS_AXIS_L_HOR 0		
#define PS_AXIS_L_VER 1
#define PS_AXIS_R_HOR 2
#define PS_AXIS_R_VER 3
#define PS_AXIS_L2 4
#define PS_AXIS_R2 5
#define PS_AXIS_DPAD_HOR 6
#define PS_AXIS_DPAD_VER 7

#define XB_FACE_DOWN 0		// A
#define XB_FACE_RIGHT 1		// B
#define XB_FACE_LEFT 2		// X
#define XB_FACE_UP 3		// Y
#define XB_LB 4				// Left Bumper
#define XB_RB 5				// Right Bumper
#define XB_L_STICK 8		// Left Stick
#define XB_R_STICK 9		// Right Stick
#define XB_SELECT 6			// Select
#define XB_START 7			// Start
#define XB_HOME 10			// Xbox
#define XB_AXIS_L_HOR 0		
#define XB_AXIS_L_VER 1
#define XB_AXIS_R_HOR 4
#define XB_AXIS_R_VER 5
#define XB_AXIS_L2_R2 2
#define XB_AXIS_DPAD_HOR 6
#define XB_AXIS_DPAD_VER 7

namespace Stellar {

	bool ControllerInput::IsConnected(unsigned int _slot)
	{
		return sf::Joystick::isConnected(_slot);
	}

	bool ControllerInput::IsPlayStation(unsigned int _slot)
	{
		return sf::Joystick::getIdentification(_slot).vendorId == PS_VID;
	}

	bool ControllerInput::IsPressed(ControllerButton _button, unsigned int _slot)
	{
		return sf::Joystick::isButtonPressed(_slot, GetSFMLButton(_button, _slot));
	}

	float ControllerInput::GetAxisValue(ControllerAxis _axis, unsigned int _slot)
	{
		float v = sf::Joystick::getAxisPosition(_slot, (sf::Joystick::Axis)GetSFMLAxis(_axis, _slot));
		float deadZone = Settings::Get().controllerDeadZone;

		if (_axis == ControllerAxis::DPAD_VER)
		{
			// For some reason the D-Pad Vertical is flipped compared to the analog sticks
			if (v > -deadZone && v < deadZone)
			{
				return 0.f;
			}

			return -v;
		}

		if (!IsPlayStation(_slot))
		{
			if (_axis == ControllerAxis::R2)
			{
				// On Xbox, the R2 value is (-) instead of (+) so this flips it back
				v = -v;
			}

			if ((_axis == ControllerAxis::L2 || _axis == ControllerAxis::R2))
			{
				return v < 0.f ? 0.f : v;
			}
		}
		else
		{
			if ((_axis == ControllerAxis::L2 || _axis == ControllerAxis::R2))
			{
				return v == 0.f ? 0.f : ((v + 100.f) / 2.f);
			}
		}

		// If the movement is below the deadZone, return 0
		bool isStick = _axis == ControllerAxis::L_HOR || _axis == ControllerAxis::L_VER || _axis == ControllerAxis::R_HOR || _axis == ControllerAxis::R_VER;
		bool isPad = _axis == ControllerAxis::DPAD_HOR || _axis == ControllerAxis::DPAD_VER;
		if (v > -deadZone && v < deadZone && (isStick || isPad))
		{
			return 0.f;
		}

		return v;
	}

	ControllerButton ControllerInput::GetButton(unsigned int _button, unsigned int _slot)
	{
		if (IsPlayStation(_slot))
		{
			switch (_button)
			{
			case PS_FACE_DOWN:
				return ControllerButton::FACE_DOWN;
			case PS_FACE_RIGHT:
				return ControllerButton::FACE_RIGHT;
			case PS_FACE_LEFT:
				return ControllerButton::FACE_LEFT;
			case PS_FACE_UP:
				return ControllerButton::FACE_UP;
			case PS_L1:
				return ControllerButton::L1;
			case PS_R1:
				return ControllerButton::R1;
			case PS_L3:
				return ControllerButton::L3;
			case PS_R3:
				return ControllerButton::R3;
			case PS_SHARE:
				return ControllerButton::SELECT;
			case PS_START:
				return ControllerButton::START;
			case PS_HOME:
				return ControllerButton::HOME;
			default:
				// Unhandled
				return ControllerButton::UNKNOWN;
			}
		}
		else
		{
			switch (_button)
			{
			case XB_FACE_DOWN:
				return ControllerButton::FACE_DOWN;
			case XB_FACE_RIGHT:
				return ControllerButton::FACE_RIGHT;
			case XB_FACE_LEFT:
				return ControllerButton::FACE_LEFT;
			case XB_FACE_UP:
				return ControllerButton::FACE_UP;
			case XB_LB:
				return ControllerButton::L1;
			case XB_RB:
				return ControllerButton::R1;
			case XB_L_STICK:
				return ControllerButton::L3;
			case XB_R_STICK:
				return ControllerButton::R3;
			case XB_SELECT:
				return ControllerButton::SELECT;
			case XB_START:
				return ControllerButton::START;
			case XB_HOME:
				return ControllerButton::HOME;
			default:
				// Unhandled
				return ControllerButton::UNKNOWN;
			}
		}
	}

	ControllerAxis ControllerInput::GetAxis(unsigned int _axis, unsigned int _slot)
	{
		if (IsPlayStation(_slot))
		{
			switch (_axis)
			{
			case PS_AXIS_L_HOR:
				return ControllerAxis::L_HOR;
			case PS_AXIS_L_VER:
				return ControllerAxis::L_VER;
			case PS_AXIS_R_HOR:
				return ControllerAxis::R_HOR;
			case PS_AXIS_R_VER:
				return ControllerAxis::R_VER;
			case PS_AXIS_L2:
				return ControllerAxis::L2;
			case PS_AXIS_R2:
				return ControllerAxis::R2;
			case PS_AXIS_DPAD_HOR:
				return ControllerAxis::DPAD_HOR;
			case PS_AXIS_DPAD_VER:
				return ControllerAxis::DPAD_VER;
			default:
				// Unhandled
				return ControllerAxis::UNKNOWN;
			}
		}
		else
		{
			switch (_axis)
			{
			case XB_AXIS_L_HOR:
				return ControllerAxis::L_HOR;
			case XB_AXIS_L_VER:
				return ControllerAxis::L_VER;
			case XB_AXIS_R_HOR:
				return ControllerAxis::R_HOR;
			case XB_AXIS_R_VER:
				return ControllerAxis::R_VER;
			case XB_AXIS_L2_R2:
			{
				float v = sf::Joystick::getAxisPosition(_slot, sf::Joystick::Z);
				return v > 0.f ? ControllerAxis::L2 : ControllerAxis::R2;
			}
			case XB_AXIS_DPAD_HOR:
				return ControllerAxis::DPAD_HOR;
			case XB_AXIS_DPAD_VER:
				return ControllerAxis::DPAD_VER;
			default:
				// Unhandled
				return ControllerAxis::UNKNOWN;
			}
		}
	}

	int ControllerInput::GetSFMLButton(ControllerButton _button, unsigned int _slot)
	{
		if (IsPlayStation(_slot))
		{
			switch (_button)
			{
			case ControllerButton::FACE_DOWN:
				return PS_FACE_DOWN;
			case ControllerButton::FACE_RIGHT:
				return PS_FACE_RIGHT;
			case ControllerButton::FACE_LEFT:
				return PS_FACE_LEFT;
			case ControllerButton::FACE_UP:
				return PS_FACE_UP;
			case ControllerButton::L1:
				return PS_L1;
			case ControllerButton::R1:
				return PS_R1;
			case ControllerButton::L3:
				return PS_L3;
			case ControllerButton::R3:
				return PS_R3;
			case ControllerButton::SELECT:
				return PS_SHARE;
			case ControllerButton::START:
				return PS_START;
			case ControllerButton::HOME:
				return PS_HOME;
			default:
				// Unhandled
				return -1;
			}
		}
		else
		{
			switch (_button)
			{
			case ControllerButton::FACE_DOWN:
				return XB_FACE_DOWN;
			case ControllerButton::FACE_RIGHT:
				return XB_FACE_RIGHT;
			case ControllerButton::FACE_LEFT:
				return XB_FACE_LEFT;
			case ControllerButton::FACE_UP:
				return XB_FACE_UP;
			case ControllerButton::L1:
				return XB_LB;
			case ControllerButton::R1:
				return XB_RB;
			case ControllerButton::L3:
				return XB_L_STICK;
			case ControllerButton::R3:
				return XB_R_STICK;
			case ControllerButton::SELECT:
				return XB_SELECT;
			case ControllerButton::START:
				return XB_START;
			case ControllerButton::HOME:
				return XB_HOME;
			default:
				// Unhandled
				return -1;
			}
		}
	}

	int ControllerInput::GetSFMLAxis(ControllerAxis _axis, unsigned int _slot)
	{
		if (IsPlayStation(_slot))
		{
			switch (_axis)
			{
			case ControllerAxis::L_HOR:
				return PS_AXIS_L_HOR;
			case ControllerAxis::L_VER:
				return PS_AXIS_L_VER;
			case ControllerAxis::R_HOR:
				return PS_AXIS_R_HOR;
			case ControllerAxis::R_VER:
				return PS_AXIS_R_VER;
			case ControllerAxis::L2:
				return PS_AXIS_L2;
			case ControllerAxis::R2:
				return PS_AXIS_R2;
			case ControllerAxis::DPAD_HOR:
				return PS_AXIS_DPAD_HOR;
			case ControllerAxis::DPAD_VER:
				return PS_AXIS_DPAD_VER;
			default:
				// Unhandled
				return -1;
			}
		}
		else
		{
			switch (_axis)
			{
			case ControllerAxis::L_HOR:
				return XB_AXIS_L_HOR;
			case ControllerAxis::L_VER:
				return XB_AXIS_L_VER;
			case ControllerAxis::R_HOR:
				return XB_AXIS_R_HOR;
			case ControllerAxis::R_VER:
				return XB_AXIS_R_VER;
			case ControllerAxis::L2:
			case ControllerAxis::R2:
				return XB_AXIS_L2_R2;
			case ControllerAxis::DPAD_HOR:
				return XB_AXIS_DPAD_HOR;
			case ControllerAxis::DPAD_VER:
				return XB_AXIS_DPAD_VER;
			default:
				// Unhandled
				return -1;
			}
		}
	}
}