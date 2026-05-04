#ifndef TOOL_PRESS_INPUT_H
#define TOOL_PRESS_INPUT_H

#include <Stellar/Stellar.h>

class ToolPress : public Stellar::DebugTool
{
public:
	ToolPress()
		: DebugTool("Press Presentation") {}

	void UpdateImGui(float _deltaTime) override;
};

#endif