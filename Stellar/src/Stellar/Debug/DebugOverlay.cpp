#include "DebugOverlay.h"

#include "Stellar/Core/Game.h"
#include "Stellar/Core/AssetManager.h"

#include "Stellar/Debug/Tools/ToolControllerInput.h"

#define IMGUI_HIDE_CLOSE 1 << 20

namespace Stellar {

	void DebugOverlay::Load()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

		float fontSize = 16.0f;
		io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/ReadexPro-Regular.ttf", fontSize);
		io.Fonts->AddFontFromFileTTF("Assets/Fonts/ReadexPro-Bold.ttf", fontSize);
		ImGui::SFML::UpdateFontTexture();

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowTitleAlign = ImVec2{ 0.5f, 0.5f };
		style.WindowRounding = 5.f;
		style.FrameRounding = 3.f;
		style.GrabRounding = 2.f;
		style.TabBorderSize = 1;
		style.FrameBorderSize = 1;

		auto& colors = style.Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 0.9f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 0.9f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 0.9f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.3f, 0.305f, 0.31f, 0.9f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.4f, 0.405f, 0.41f, 0.9f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };

		// Frame Background
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 0.9f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 0.9f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 0.9f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 0.9f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 0.9f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 0.9f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.1f, 0.1f, 0.1f, 0.9f };

		RegisterTool<ToolControllerInput>();
	}

	void DebugOverlay::UpdateImGui(const std::shared_ptr<GameState>& _gameState, float _deltaTime)
	{
		if (!isDebugEnabled)
		{
			return;
		}

		static bool settingsOpen = false;
		static bool gameStateOpen = false;
		static bool aboutOpen = false;

		if (settingsOpen)
		{
			UpdateSettings(&settingsOpen);
		}
		if (gameStateOpen)
		{
			UpdateGameState(_gameState, _deltaTime, &gameStateOpen);
		}
		if (aboutOpen)
		{
			UpdateAbout(aboutOpen);
		}
		for (auto& tool : tools)
		{
			if (tool->isEnabled)
			{
				if (ImGui::Begin(tool->GetName().c_str(), &tool->isEnabled))
				{
					tool->UpdateImGui(_deltaTime);
				}
				ImGui::End();
			}
		}

		ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
		ImGui::Begin("Stellar - Debug", &isDebugEnabled, flags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Settings", nullptr, &settingsOpen);
				ImGui::MenuItem("GameState", nullptr, &gameStateOpen);
				ImGui::EndMenu();
			}
			if (!tools.empty())
			{
				if (ImGui::BeginMenu("Tools"))
				{
					for (auto& tool : tools)
					{
						ImGui::MenuItem(tool->GetName().c_str(), nullptr, &tool->isEnabled);
					}
					ImGui::EndMenu();
				}
			}
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About"))
				{
					aboutOpen = true;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		UpdateStats(_gameState, _deltaTime);
		ImGui::End();
	}

	DebugOverlay& DebugOverlay::Get()
	{
		if (!instance)
		{
			instance = new DebugOverlay();
		}
		return *instance;
	}

	void DebugOverlay::Shutdown()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void DebugOverlay::UpdateStats(const std::shared_ptr<GameState>& _gameState, float _deltaTime)
	{
		ImGui::Text("DeltaTime: %f", _deltaTime);
		{
			float fps = 1.f / _deltaTime;
			ImGui::Text("FPS: %.2f", fps);
			static bool trackFPS = false;
			static std::vector<float> fpsHistory;
			if (trackFPS)
			{
				fpsHistory.push_back(fps);
				if (fpsHistory.size() > 100)
				{
					fpsHistory.erase(fpsHistory.begin()); // Keep size at 100
				}
			}
			ImGui::SameLine();
			if (ImGui::Button(trackFPS ? "Stop Profiling" : "Start Profiling"))
			{
				trackFPS = !trackFPS;
			}
			if (!fpsHistory.empty())
			{
				bool clearedHistory = false;
				ImGui::SameLine();
				if (ImGui::Button("Clear"))
				{
					clearedHistory = true;
				}
				float averageFps = 0.f;
				for (float f : fpsHistory)	
				{
					averageFps += f;
				}
				averageFps /= fpsHistory.size();
				ImGui::Text("Average: %.2f", averageFps);
				auto [minFps, maxFps] = std::minmax_element(fpsHistory.begin(), fpsHistory.end());
				float padding = 10.0f;
				float minRange = std::max(0.0f, *minFps - padding);
				float maxRange = *maxFps + padding;
				ImGui::PlotLines("##fps_history", fpsHistory.data(), (int)fpsHistory.size(), 0, nullptr, minRange, maxRange, ImVec2(0, 50));

				if (clearedHistory)
				{
					fpsHistory.clear();
				}
			}
		}

		ImGui::Text("Display Size: %dx%d", Settings::Get().videoMode.width, Settings::Get().videoMode.height);
		ImGui::Text("GameState: %s", _gameState ? _gameState->GetDebugName().c_str() : "None");
	}

	void DebugOverlay::UpdateSettings(bool* _open)
	{
		if (ImGui::Begin("Settings", _open))
		{
			ImGui::PushItemWidth(150.f);
			if (ImGui::CollapsingHeader("General"))
			{
				const char* items[]{ "EN_US", "FR_FR" };
				int selectedItem = (int)Settings::Get().language;
				if (ImGui::Combo("Language", &selectedItem, items, IM_ARRAYSIZE(items)))
				{
					std::string lang = std::string(items[selectedItem]);
					LangType langType = Language::LangStrToEnum(lang);
					Language::Get().SetLanguage(langType);
					Settings::Get().language = langType;
				}
				const char* qualityItems[]{ "Low", "Medium", "High" };
				int selectedPreset = (int)Settings::Get().graphicsPreset;
				if (ImGui::Combo("Graphics Preset", &selectedPreset, qualityItems, IM_ARRAYSIZE(qualityItems)))
				{
					Settings::Get().graphicsPreset = (GraphicsPreset)selectedPreset;
				}

				ImGui::DragFloat("UI Scale", &Settings::Get().uiScale, 0.25f, 0.75f, 1.25f);
			}
				
			if (ImGui::CollapsingHeader("Display"))
			{
				bool toggleFullscreen = Settings::Get().isFullscreen;
				if (ImGui::Checkbox("Fullscreen", &toggleFullscreen))
				{
					Game::Get().ToggleFullscreen(toggleFullscreen);
				}
				bool toggleVSync = Settings::Get().isVSync;
				if (ImGui::Checkbox("VSync", &toggleVSync))
				{
					Settings::Get().isVSync = toggleVSync;
					Game::Get().GetRenderWindow().setVerticalSyncEnabled(toggleVSync);
				}
				int fpsLimit = (int)Settings::Get().fpsLimit;
				if (ImGui::DragInt("FPS Limit", &fpsLimit, 1.f, 0, 244))
				{
					Settings::Get().fpsLimit = fpsLimit;
					Game::Get().GetRenderWindow().setFramerateLimit(fpsLimit);
				}
				int winSize[2] = { (int)Settings::GetWindowSize().x, (int)Settings::GetWindowSize().y };
				if (ImGui::DragInt2("Window Size", winSize))
				{
					Game::Get().GetRenderWindow().setSize({ (unsigned int)winSize[0], (unsigned int)winSize[1] });
				}
			}

			if (ImGui::CollapsingHeader("Audio"))
			{
				int masterVolume = Settings::Get().volumeMaster;
				if (ImGui::DragInt("Master Volume", &masterVolume, 1.f, 0, 100, "%d%%"))
				{
					Settings::Get().volumeMaster = masterVolume;
				}
				int musicVolume = Settings::Get().volumeMusic;
				if (ImGui::DragInt("Music Volume", &musicVolume, 1.f, 0, 100, "%d%%"))
				{
					Settings::Get().volumeMusic = musicVolume;
				}
				int uiVolume = Settings::Get().volumeUI;
				if (ImGui::DragInt("UI Volume", &uiVolume, 1.f, 0, 100, "%d%%"))
				{
					Settings::Get().volumeUI = uiVolume;
				}
				int sfxVolume = Settings::Get().volumeSFX;
				if (ImGui::DragInt("SFX Volume", &sfxVolume, 1.f, 0, 100, "%d%%"))
				{
					Settings::Get().volumeSFX = sfxVolume;
				}
			}

			if (ImGui::CollapsingHeader("Input"))
			{
				float deadZone = Settings::Get().controllerDeadZone;
				if (ImGui::DragFloat("Controller Deadzone", &deadZone, 1.f, 0.f, 100.f, "%.0f%%"))
				{
					Settings::Get().controllerDeadZone = deadZone;
				}
			}
			ImGui::PopItemWidth();
		}
		ImGui::End();
	}

	void DebugOverlay::UpdateGameState(const std::shared_ptr<GameState>& _gameState, float _deltaTime, bool* _open)
	{
		if (_gameState)
		{
			if (ImGui::Begin(_gameState->GetDebugName().c_str(), _open))
			{
				_gameState->UpdateImGui(_deltaTime);
				if (ImGui::Button("Reload GameState"))
				{
					_gameState->Load();
					_gameState->OnResize(Settings::GetWindowSize());
				}
			}
			ImGui::End();
		}
	}

	void DebugOverlay::UpdateAbout(bool& _open)
	{
		if (_open)
		{
			ImGui::OpenPopup("About Stellar");
		}

		if (ImGui::BeginPopupModal("About Stellar", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImVec2 popupSize = ImGui::GetWindowSize();
			ImVec2 logoSize = ImVec2(80.f, 80.f);
			ImVec2 logoPos = ImVec2((popupSize.x - logoSize.x) / 2.f, 35.f);
			ImGui::SetCursorPos(logoPos);
			ImGui::Image(AssetManager::GetTexture("Logo.png").getNativeHandle(), logoSize, {0, 1}, {1, 0});
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[2]);
			const char* titleText = "Stellar Engine";
			ImGui::Text(titleText);
			ImGui::PopFont();

			const std::string aboutText = std::format("Version: {}\n\nMade with <3\nhttps://github.com/ImNotStealth/Stellar", STELLAR_VER);
			ImGui::Text(aboutText.c_str());

			ImVec2 buttonSize = ImVec2(120, 0);
			ImVec2 titleTextSize = ImGui::CalcTextSize(titleText);
			ImVec2 aboutTextSize = ImGui::CalcTextSize(aboutText.c_str());
			ImVec2 buttonPos = ImVec2((popupSize.x - buttonSize.x) / 2.f, logoSize.y + 15.f + titleTextSize.y + 5.0f + aboutTextSize.y + 5.0f + ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing());
			ImGui::SetCursorPos(buttonPos);
			if (ImGui::Button("Close", buttonSize))
			{
				ImGui::CloseCurrentPopup();
				_open = false;
			}
			ImGui::EndPopup();
		}
	}
}
