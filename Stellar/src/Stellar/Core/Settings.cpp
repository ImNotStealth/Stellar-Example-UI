#include "Settings.h"

#include <cstdio>
#include <sstream>

#define SETTINGS_MESSAGE "Well well well... What do we have here?"

namespace Stellar {

	void Settings::LoadFromFile()
	{
		std::filesystem::path filePath = "Settings.cfg";
		std::ifstream file(filePath);

		if (!file.is_open())
		{
			SaveToFile();
			return;
		}

		std::string line;
		std::getline(file, line); // SETTINGS_MESSAGE
		std::getline(file, line); // \n
		std::getline(file, line); // [General]
		ParseSetting(file, line, language);
		ParseSetting(file, line, graphicsPreset);
		ParseSetting(file, line, uiScale);
		std::getline(file, line); // \n
		std::getline(file, line); // [Display]
		ParseSetting(file, line, isFullscreen);
		ParseSetting(file, line, isVSync);
		ParseSetting(file, line, fpsLimit);
		ParseSetting(file, line, winSize.x);
		ParseSetting(file, line, winSize.y);
		std::getline(file, line); // \n
		std::getline(file, line); // [Sound]
		ParseSetting(file, line, volumeMaster);
		ParseSetting(file, line, volumeMusic);
		ParseSetting(file, line, volumeUI);
		ParseSetting(file, line, volumeSFX);
		std::getline(file, line); // \n
		std::getline(file, line); // [Input]
		ParseSetting(file, line, controllerDeadZone);
		file.close();

		std::cout << "Loaded Settings." << std::endl;
	}

	void Settings::SaveToFile()
	{
		std::filesystem::path filePath = "Settings.cfg";
		std::ofstream file(filePath);

		if (!file.is_open())
		{
			std::cerr << "Failed to save to Settings file." << std::endl;
			return;
		}

		file << SETTINGS_MESSAGE << std::endl;
		file << std::endl;
		file << "[General]" << std::endl;
		WriteSetting(file, "Language", language);
		WriteSetting(file, "GraphicsPreset", graphicsPreset);
		WriteSetting(file, "UIScale", uiScale);
		file << std::endl;
		file << "[Display]" << std::endl;
		WriteSetting(file, "Fullscreen", isFullscreen);
		WriteSetting(file, "VSync", isVSync);
		WriteSetting(file, "FPSLimit", fpsLimit);
		WriteSetting(file, "WindowWidth", winSize.x);
		WriteSetting(file, "WindowHeight", winSize.y);
		file << std::endl;
		file << "[Sound]" << std::endl;
		WriteSetting(file, "MasterVolume", volumeMaster);
		WriteSetting(file, "MusicVolume", volumeMusic);
		WriteSetting(file, "UIVolume", volumeUI);
		WriteSetting(file, "SFXVolume", volumeSFX);
		file << std::endl;
		file << "[Input]" << std::endl;
		WriteSetting(file, "ControllerDeadZone", controllerDeadZone);
		file.close();

		std::cout << "Saved Settings." << std::endl;
	}

	Settings& Settings::Get()
	{
		if (!instance)
		{
			instance = new Settings();
			instance->videoMode = sf::VideoMode::getDesktopMode();
		}
		return *instance;
	}

	void Settings::Shutdown()
	{
		if (instance)
		{
			instance->SaveToFile();
			delete instance;
			instance = nullptr;
		}
	}

	sf::Vector2u Settings::GetWindowSize()
	{
		return Get().isFullscreen ? sf::Vector2u(Get().videoMode.width, Get().videoMode.height) : Get().winSize;
	}

	template<typename T>
	bool Settings::ParseSetting(std::ifstream& _stream, std::string& _line, T& _value)
	{
		std::getline(_stream, _line);
		size_t pos = _line.find('=');
		if (pos != std::string::npos)
		{
			std::istringstream iss(_line.substr(pos + 1));
			iss >> _value;
			return !iss.fail();
		}
		return false;
	}

	template<typename T>
	void Settings::WriteSetting(std::ofstream& _file, const std::string& _name, const T& _value)
	{
		_file << _name << '=' << _value << std::endl;
	}
}