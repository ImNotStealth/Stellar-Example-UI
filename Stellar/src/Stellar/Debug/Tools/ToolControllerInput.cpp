#include "ToolControllerInput.h"

#include "Stellar/Core/Settings.h"
#include "Stellar/Utils/ControllerInput.h"

namespace Stellar
{
	void ToolControllerInput::UpdateImGui(float _deltaTime)
	{
		ImGui::Text("Controller ID:");
		ImGui::SameLine();
		ImGui::PushItemWidth(100.f);
		ImGui::SliderInt("##controllerID", (int*)(&controllerSlot), 0, sf::Joystick::Count);
		ImGui::PopItemWidth();

		bool isConnected = ControllerInput::IsConnected(controllerSlot);
		if (!isConnected)
		{
			ImGui::Text("No controller connected.");
			return;
		}

		bool isPS = ControllerInput::IsPlayStation(controllerSlot);

		ImGui::Text("Mapping: %s", isPS ? "PlayStation" : "Xbox");
		ImGui::Text("");
		ImGui::Text("Face Down: %d", ControllerInput::IsPressed(ControllerButton::FACE_DOWN, controllerSlot));
		ImGui::Text("Face Left: %d", ControllerInput::IsPressed(ControllerButton::FACE_LEFT, controllerSlot));
		ImGui::Text("Face Right: %d", ControllerInput::IsPressed(ControllerButton::FACE_RIGHT, controllerSlot));
		ImGui::Text("Face Up: %d", ControllerInput::IsPressed(ControllerButton::FACE_UP, controllerSlot));
		ImGui::Text("L1: %d", ControllerInput::IsPressed(ControllerButton::L1, controllerSlot));
		ImGui::Text("R1: %d", ControllerInput::IsPressed(ControllerButton::R1, controllerSlot));
		ImGui::Text("L3: %d", ControllerInput::IsPressed(ControllerButton::L3, controllerSlot));
		ImGui::Text("R3: %d", ControllerInput::IsPressed(ControllerButton::R3, controllerSlot));
		ImGui::Text("Select: %d", ControllerInput::IsPressed(ControllerButton::SELECT, controllerSlot));
		ImGui::Text("Start: %d", ControllerInput::IsPressed(ControllerButton::START, controllerSlot));
		ImGui::Text("Home: %d", ControllerInput::IsPressed(ControllerButton::HOME, controllerSlot));
		ImGui::Text("");
		ImGui::Text("L Hor: %f", ControllerInput::GetAxisValue(ControllerAxis::L_HOR, controllerSlot));
		ImGui::Text("L Ver: %f", ControllerInput::GetAxisValue(ControllerAxis::L_VER, controllerSlot));
		ImGui::Text("R Hor: %f", ControllerInput::GetAxisValue(ControllerAxis::R_HOR, controllerSlot));
		ImGui::Text("R Ver: %f", ControllerInput::GetAxisValue(ControllerAxis::R_VER, controllerSlot));
		ImGui::Text("D-Pad Hor: %f", ControllerInput::GetAxisValue(ControllerAxis::DPAD_HOR, controllerSlot));
		ImGui::Text("D-Pad Ver: %f", ControllerInput::GetAxisValue(ControllerAxis::DPAD_VER, controllerSlot));
		ImGui::Text("L2: %f", ControllerInput::GetAxisValue(ControllerAxis::L2, controllerSlot));
		ImGui::Text("R2: %f", ControllerInput::GetAxisValue(ControllerAxis::R2, controllerSlot));

		ImVec2 winSize = ImGui::GetWindowSize();
		ImVec2 winPos = ImGui::GetWindowPos();

		float scaleFactor = winSize.y / 2.f;
		ImVec2 layoutSize(scaleFactor, scaleFactor);
		ImVec2 layoutPos = { winPos.x + (winSize.x - layoutSize.x) / 2.f, winPos.y + (winSize.y - layoutSize.y) / 2.f };

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 center = ImVec2(layoutPos.x + layoutSize.x / 2.f, layoutPos.y + layoutSize.y / 2.f);

		DrawButton({ center.x, center.y + (isPS ? +layoutSize.y / 3.f : -layoutSize.y / 3.f)}, scaleFactor / 10.f, ControllerButton::HOME);
		DrawButton({ center.x - scaleFactor / 5.f, center.y }, scaleFactor / 15.f, ControllerButton::SELECT);
		DrawButton({ center.x + scaleFactor / 5.f, center.y }, scaleFactor / 15.f, ControllerButton::START);

		ImVec2 buttonPos = { center.x + layoutSize.x / 1.2f, center.y };
		DrawButton({ buttonPos.x, buttonPos.y + scaleFactor / 6.f }, scaleFactor / 10.f, ControllerButton::FACE_DOWN);
		DrawButton({ buttonPos.x - scaleFactor / 6.f, buttonPos.y }, scaleFactor / 10.f, ControllerButton::FACE_LEFT);
		DrawButton({ buttonPos.x, buttonPos.y - scaleFactor / 6.f }, scaleFactor / 10.f, ControllerButton::FACE_UP);
		DrawButton({ buttonPos.x + scaleFactor / 6.f, buttonPos.y }, scaleFactor / 10.f, ControllerButton::FACE_RIGHT);

		ImVec2 bumperPos = { center.x, center.y - layoutSize.y / 2.f };
		DrawBumper({ bumperPos.x - scaleFactor / 1.5f - scaleFactor / 5.f, bumperPos.y }, scaleFactor / 10.f, ControllerButton::L1);
		DrawBumper({ bumperPos.x + scaleFactor / 1.5f, bumperPos.y }, scaleFactor / 10.f, ControllerButton::R1);

		ImVec2 leftStickPos = { center.x - layoutSize.x / 1.2f, center.y };
		ImVec2 dpadPos = { center.x - layoutSize.x / 3.f, center.y + layoutSize.y / 2.f };
		DrawStick(isPS ? dpadPos : leftStickPos, scaleFactor / 5.f, ControllerAxis::L_HOR, ControllerAxis::L_VER, ControllerButton::L3);

		ImVec2 rightStickPos = { center.x + layoutSize.x / 3.f, center.y + layoutSize.y / 2.f };
		DrawStick(rightStickPos, scaleFactor / 5.f, ControllerAxis::R_HOR, ControllerAxis::R_VER, ControllerButton::R3);

		DrawDPad(isPS ? leftStickPos : dpadPos, scaleFactor / 9.f);

		DrawTrigger({ bumperPos.x - scaleFactor / 1.5f - scaleFactor / 5.f, bumperPos.y - scaleFactor / 3.f }, scaleFactor / 10.f, ControllerAxis::L2);
		DrawTrigger({ bumperPos.x + scaleFactor / 1.5f, bumperPos.y - scaleFactor / 3.f }, scaleFactor / 10.f, ControllerAxis::R2);
	}

	void ToolControllerInput::DrawButton(ImVec2 _pos, float _radius, ControllerButton _button)
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		if (ControllerInput::IsPressed(_button, controllerSlot))
			drawList->AddCircleFilled(_pos, _radius, IM_COL32(255, 255, 255, 255), 25);
		else
			drawList->AddCircle(_pos, _radius, IM_COL32(255, 255, 255, 255), 25, _radius / 20.f);
	}

	void ToolControllerInput::DrawBumper(ImVec2 _pos, float _scale, ControllerButton _button)
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		if (ControllerInput::IsPressed(_button, controllerSlot))
			drawList->AddRectFilled(_pos, { _pos.x + _scale * 2.f, _pos.y + _scale }, IM_COL32(255, 255, 255, 255), 5);
		else
			drawList->AddRect(_pos, { _pos.x + _scale * 2.f, _pos.y + _scale }, IM_COL32(255, 255, 255, 255), 5);
	}

	void ToolControllerInput::DrawStick(ImVec2 _pos, float _radius, ControllerAxis _axisH, ControllerAxis _axisV, ControllerButton _stickButton)
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		float hor = ControllerInput::GetAxisValue(_axisH, controllerSlot);
		float ver = ControllerInput::GetAxisValue(_axisV, controllerSlot);

		drawList->AddCircle({ _pos.x, _pos.y }, _radius, IM_COL32(255, 255, 255, 255), 25, _radius / 10.f);

		if (ControllerInput::IsPressed(_stickButton, controllerSlot))
			drawList->AddCircleFilled({ _pos.x + hor / 2.f, _pos.y + ver / 2.f }, _radius * 0.8f, IM_COL32(255, 255, 255, 255), 25);
		else
			drawList->AddCircle({ _pos.x + hor / 2.f, _pos.y + ver / 2.f }, _radius * 0.8f, IM_COL32(255, 255, 255, 255), 25, _radius / 5.f);
	}

	void ToolControllerInput::DrawDPad(ImVec2 _pos, float _scale)
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 dpadRight = { _pos.x + _scale * 0.9f, _pos.y - _scale * 0.75f };
		if (ControllerInput::GetAxisValue(ControllerAxis::DPAD_HOR, controllerSlot) > 0.f)
			drawList->AddRectFilled(dpadRight, { dpadRight.x + _scale * 1.5f, dpadRight.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5);
		else
			drawList->AddRect(dpadRight, { dpadRight.x + _scale * 1.5f, dpadRight.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5, 0, _scale / 20.f);

		ImVec2 dpadLeft = { _pos.x - _scale * 1.5f - _scale * 0.9f, _pos.y - _scale * 0.75f };
		if (ControllerInput::GetAxisValue(ControllerAxis::DPAD_HOR, controllerSlot) < 0.f)
			drawList->AddRectFilled(dpadLeft, { dpadLeft.x + _scale * 1.5f, dpadLeft.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5);
		else
			drawList->AddRect(dpadLeft, { dpadLeft.x + _scale * 1.5f, dpadLeft.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5, 0, _scale / 20.f);

		ImVec2 dpadUp = { _pos.x - _scale * 0.75f, _pos.y - _scale * 1.5f - _scale * 0.9f };
		if (ControllerInput::GetAxisValue(ControllerAxis::DPAD_VER, controllerSlot) < 0.f)
			drawList->AddRectFilled(dpadUp, { dpadUp.x + _scale * 1.5f, dpadUp.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5);
		else
			drawList->AddRect(dpadUp, { dpadUp.x + _scale * 1.5f, dpadUp.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5, 0, _scale / 20.f);

		ImVec2 dpadDown = { _pos.x - _scale * 0.75f, _pos.y + _scale * 0.9f };
		if (ControllerInput::GetAxisValue(ControllerAxis::DPAD_VER, controllerSlot) > 0.f)
			drawList->AddRectFilled(dpadDown, { dpadDown.x + _scale * 1.5f, dpadDown.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5);
		else
			drawList->AddRect(dpadDown, { dpadDown.x + _scale * 1.5f, dpadDown.y + _scale * 1.5f }, IM_COL32(255, 255, 255, 255), 5, 0, _scale / 20.f);
	}

	void ToolControllerInput::DrawTrigger(ImVec2 _pos, float _scale, ControllerAxis _axis)
	{
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		float value = ControllerInput::GetAxisValue(_axis, controllerSlot);

		ImVec2 max = { _pos.x + _scale * 2.f, _pos.y + _scale * 2.5f };
		drawList->AddRect(_pos, max, IM_COL32(255, 255, 255, 255), 5);

		ImVec2 startPos = { _pos.x, _pos.y - _scale * 2.5f + (_scale * 2.5f + (_scale * 2.5f * ((100.f - value) / 100.f))) };
		drawList->AddRectFilled(startPos, { startPos.x + _scale * 2.f, startPos.y + _scale * 2.5f - (_scale * 2.5f * ((100.f - value) / 100.f)) }, IM_COL32(255, 255, 255, 255), 5);
	}
}