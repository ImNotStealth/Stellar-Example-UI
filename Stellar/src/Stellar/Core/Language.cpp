#include "Language.h"

namespace Stellar {

	void Language::SetLanguage(LangType _lang)
	{
		system("@chcp 65001>nul"); // TEMP for enabling UTF-8 in console
		std::filesystem::path filePath = std::format("Assets/Lang/{}.lang", LangEnumToStr(_lang));
		std::ifstream file(filePath);

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << filePath << std::endl;
			return;
		}

		langMap.clear();
		std::string line;
		while (std::getline(file, line))
		{
			// Trim leading and trailing spaces
			line.erase(0, line.find_first_not_of(" \t"));
			line.erase(line.find_last_not_of(" \t") + 1);

			if (line.empty())
			{
				continue;
			}

			size_t splitPos = line.find('=');

			if (splitPos == std::string::npos)
			{
				std::cout << "Found invalid line in " << filePath << ": " << line << std::endl;
				continue;
			}

			std::string key = line.substr(0, splitPos);
			std::string value = line.substr(splitPos + 1);

			// Trim leading and trailing spaces
			key.erase(0, key.find_first_not_of(" \t"));  
			key.erase(key.find_last_not_of(" \t") + 1);
			value.erase(0, value.find_first_not_of(" \t"));
			value.erase(value.find_last_not_of(" \t") + 1);

			langMap.emplace(key, value);
		}
		file.close();
		std::cout << "Set language to: " << LangEnumToStr(_lang) << std::endl;
	}

	sf::String Language::Translate(const std::string& _key)
	{
		if (!langMap.contains(_key))
		{
			return _key;
		}
		std::string str = langMap.at(_key);
		return sf::String::fromUtf8(str.begin(), str.end());
	}

	std::string Language::LangEnumToStr(LangType _lang)
	{
		switch (_lang)
		{
		case FR_FR:
			return "FR_FR";

		case EN_US:
		default:
			return "EN_US";
		}
	}

	LangType Language::LangStrToEnum(std::string& _lang)
	{
		if (_lang.compare("EN_US") == 0)
		{
			return EN_US;
		}
		else if (_lang.compare("FR_FR") == 0)
		{
			return FR_FR;
		}
		else
		{
			return EN_US;
		}
	}

	Language& Language::Get()
	{
		static Language instance;
		return instance;
	}
}
