#ifndef STELLAR_TEXT_H
#define STELLAR_TEXT_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class Text
	{
	public:
		static Text Create(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize = 30);
		static Text CreateCentered(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize = 30);

		void Center();
		void SetCharacterSize(unsigned int _fontSize);
		void SetPosition(sf::Vector2f _pos);
		void Move(sf::Vector2f _pos);
		void SetString(const sf::String& _content);
		void SetColor(sf::Color _color);
		void Draw(sf::RenderTexture& _rt);

	public:
		sf::Text frontText;
		sf::Vector2f pos;
		float fontSize = 30.f;

	private:
		bool isCentered = false;
		sf::Color color = sf::Color::White;
		friend class Paragraph;
	};
}

#endif