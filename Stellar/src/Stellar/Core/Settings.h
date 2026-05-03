#ifndef STELLAR_SETTINGS_H
#define STELLAR_SETTINGS_H

#include "Stellar/Core/Common.h"
#include "Stellar/Core/Language.h"

namespace Stellar {

	enum GraphicsPreset
	{
		LOW,
		MEDIUM,
		HIGH
	};

	class Settings
	{
	public:
		void LoadFromFile();
		void SaveToFile();
	
		static Settings& Get();
		static void Shutdown();

		static sf::Vector2u GetWindowSize();
	public:
		// General
		LangType language = LangType::EN_US;
		GraphicsPreset graphicsPreset = GraphicsPreset::MEDIUM;
		float uiScale = 1.f;

		// Display
		bool isFullscreen = false;
		bool isVSync = false;
		unsigned int fpsLimit = 60;
		sf::Vector2u winSize;

		// Sound
		unsigned int volumeMaster = 70;
		unsigned int volumeMusic = 100;
		unsigned int volumeUI = 100;
		unsigned int volumeSFX = 100;

		// Input
		unsigned int controllerID = 0;
		float controllerDeadZone = 50.f;

		//Not Saved
		sf::VideoMode videoMode;

	private:
		inline static Settings* instance = nullptr;

	private:
		template<typename T>
		bool ParseSetting(std::ifstream& _stream, std::string& _line, T& _value);

		template<typename T>
		void WriteSetting(std::ofstream& _file, const std::string& _name, const T& _value);
	};

	inline std::istream& operator>>(std::istream& _in, GraphicsPreset& _preset)
	{
		std::string input;
		_in >> input;

		_preset = (GraphicsPreset)atoi(input.c_str());

		return _in;
	}

	inline std::ostream& operator<<(std::ostream& _os, const GraphicsPreset& _preset)
	{
		_os << (int)_preset;
		return _os;
	}
}

#endif