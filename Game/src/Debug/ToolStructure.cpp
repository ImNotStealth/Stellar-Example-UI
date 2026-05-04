#include "ToolStructure.h"

REGISTER_DEBUG_TOOL(ToolStructure)

using namespace Stellar;

void ToolStructure::UpdateImGui(float _deltaTime)
{
	/*if (!Game::Get().IsState<StateSandbox>())
	{
		ImGui::Text("Not in game!");
		return;
	}*/

    ImGui::Text("If your structure is being cut off (due to being too big),\ntry increasing 'Simulation Distance' in the Settings menu");
    ImGui::Spacing();

    RenderDirectoryContents("Assets/Structures");
}

void ToolStructure::RenderDirectoryContents(const std::filesystem::path& _directoryPath)
{
    std::vector<std::filesystem::path> directories;
    std::vector<std::filesystem::path> files;

    if (!std::filesystem::exists(_directoryPath))
    {
        ImGui::Text("Structure directory does not exist: %s", _directoryPath.string().c_str());
        return;
	}

    for (const auto& entry : std::filesystem::directory_iterator(_directoryPath))
    {
        if (std::filesystem::is_directory(entry))
            directories.push_back(entry);
        else
            files.push_back(entry);
    }

    for (const auto& dir : directories)
    {
        std::string dirName = dir.filename().string();
        if (ImGui::CollapsingHeader(dirName.c_str()))
        {
            ImGui::Indent();

            RenderDirectoryContents(dir);

            ImGui::Unindent();
        }
    }

    /*const auto& state = Game::Get().GetState<StateSandbox>();
    World& world = state->GetWorld();
    Player& player = state->GetPlayer();

    for (const auto& file : files)
    {
        std::string fileName = file.filename().string();

        if (ImGui::Button(fileName.c_str()))
        {
            std::string prefix = "Assets/Structures/", suffix = ".bin";
            std::string trimmedName = file.string().substr(prefix.size());
            trimmedName = trimmedName.substr(0, trimmedName.size() - suffix.size());
            world.PlaceStructure((unsigned int)player.GetPosition().x, (unsigned int)(-player.GetPosition().y), trimmedName);
        }
    }*/
}