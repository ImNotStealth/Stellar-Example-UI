#ifndef TOOL_STRUCTURE_INPUT_H
#define TOOL_STRUCTURE_INPUT_H

#include <Stellar/Stellar.h>

class ToolStructure : public Stellar::DebugTool
{
public:
	ToolStructure()
		: DebugTool("Structure Tools") {}

	void UpdateImGui(float _deltaTime) override;

private:
	void RenderDirectoryContents(const std::filesystem::path& _directoryPath);
};

#endif