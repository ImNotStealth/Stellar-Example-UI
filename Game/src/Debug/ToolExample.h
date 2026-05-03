#ifndef TOOL_EXAMPLE_H
#define TOOL_EXAMPLE_H

#include <Stellar/Stellar.h>

class ToolExample : public Stellar::DebugTool
{
public:
	ToolExample()
		: DebugTool("Example Tool") {}

	void UpdateImGui(float _deltaTime) override;
};

#endif