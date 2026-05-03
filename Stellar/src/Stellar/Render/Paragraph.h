#ifndef STELLAR_PARAGRAPH_H
#define STELLAR_PARAGRAPH_H

#include "Stellar/Core/Common.h"
#include "Stellar/Render/Text.h"

namespace Stellar
{
	class Paragraph
	{
	public:
		static Paragraph Create(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize = 30);
		static Paragraph CreateCentered(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize = 30);

		void Center();
		void SetScale(float _scale);
		void SetPosition(sf::Vector2f _pos);
		void SetCharacterSize(unsigned int _size);
		void SetString(const sf::String& _content);
		void Draw(sf::RenderTexture& _rt);

	public:
		sf::Vector2f pos;
	
	private:
		unsigned int fontSize;
		std::vector<sf::String> strings;
		Text text;
		std::filesystem::path fontPath;
		bool isCentered;
		float scale;
	};
}

#endif