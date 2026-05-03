#ifndef STELLAR_TOOL_CONTROLLER_INPUT_H
#define STELLAR_TOOL_CONTROLLER_INPUT_H

#include "Stellar/Debug/DebugTool.h"
#include "Stellar/Debug/DebugOverlay.h"
#include "Stellar/Utils/ControllerInput.h"

namespace Stellar
{
	class ToolControllerInput : public DebugTool
	{
	public:
		ToolControllerInput()
			: DebugTool("Controller Input") {}

		void UpdateImGui(float _deltaTime) override;

	private:
		void DrawButton(ImVec2 _pos, float _radius, ControllerButton _button);
		void DrawBumper(ImVec2 _pos, float _scale, ControllerButton _button);
		void DrawStick(ImVec2 _pos, float _radius, ControllerAxis _axisH, ControllerAxis _axisV, ControllerButton _stickButton);
		void DrawDPad(ImVec2 _pos, float _scale);
		void DrawTrigger(ImVec2 _pos, float _scale, ControllerAxis _axis);

	private:
		unsigned int controllerSlot = 0;
	};
}

#endif