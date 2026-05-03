#ifndef STELLAR_LANGUAGE_H
#define STELLAR_LANGUAGE_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	enum LangType
	{
		EN_US, // English (United-States)
		FR_FR, // French (France)
	};

	class Language
	{
	public:
		// Sets the language used in the game. Reloads stored translations.
		void SetLanguage(LangType _lang);

		/*
			Used to get the translation with the provided key.
			Returns the key if no translation is found.
			sf::String is used to convert to UTF-8 to allow for special characters.
		*/
		sf::String Translate(const std::string& _key);

		/*
			Allows to use placeholders in translations.
			Example:
			in en_US.lang: a.test=Yay {} formatting!
			in code: Language::Format("a.test", "for");
		*/
		template<typename... Args>
		sf::String Format(const std::string& _key, Args ..._args)
		{
			std::wstring str = Translate(_key).toWideString();
			std::vector<std::wstring> values = { ToWString(_args)... };

			size_t pos = 0;
			size_t index = 0;

			// Replace each '{}' placeholder with corresponding value
			while ((pos = str.find(L"{}")) != std::wstring::npos)
			{
				if (index >= values.size())
				{
					std::cout << "Language::Format Not enough arguments provided for formatting." << std::endl;
					break;
				}
				str.replace(pos, 2, values[index++]);
			}

			return sf::String(str);
		}

		// Get the instance of Language.
		static Language& Get();

		static std::string LangEnumToStr(LangType _lang);
		static LangType LangStrToEnum(std::string& _lang);

	private:
		template <typename T>
		std::wstring ToWString(const T& _value)
		{
			std::wstringstream wss;
			wss << _value;
			return wss.str();
		}

	private:
		std::map<std::string, std::string> langMap;
	};

	inline std::istream& operator>>(std::istream& _in, LangType& _lang)
	{
		std::string input;
		_in >> input;

		_lang = Language::LangStrToEnum(input);

		return _in;
	}

	inline std::ostream& operator<<(std::ostream& _os, const LangType& _lang)
	{
		_os << Language::LangEnumToStr(_lang);
		return _os;
	}
}


#endif