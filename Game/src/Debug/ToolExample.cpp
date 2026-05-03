#include "ToolExample.h"

REGISTER_DEBUG_TOOL(ToolExample)

using namespace Stellar;

void ToolExample::UpdateImGui(float _deltaTime)
{
	ImGui::Text("This tool is accessible regardless of your current state!");
	if (ImGui::Button("Example button"))
		std::cout << "Tool button pressed" << std::endl;
}