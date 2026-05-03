#ifndef STELLAR_TEXTBOX_H
#define STELLAR_TEXTBOX_H

#include "Stellar/Core/Common.h"
#include "Stellar/Render/Text.h"

namespace Stellar
{
	class Textbox
	{
	public:
		static Textbox Create(const std::filesystem::path& _fontPath, const std::string& _langPlaceholderKey, sf::Vector2f _pos, bool _bg = true, unsigned int _fontSize = 30);
		static Textbox CreateCentered(const std::filesystem::path& _fontPath, const std::string& _langPlaceholderKey, sf::Vector2f _pos, bool _bg = true, unsigned int _fontSize = 30);

		void OnMousePressed(sf::Event::MouseButtonEvent _mouse);
		void OnTextEntered(sf::Event::TextEvent _text);
		void Draw(sf::RenderTexture& _rt);
		void SetPosition(sf::Vector2f _pos);
		void SetLabelContent(const std::string& _placeholderKey);
		void SetFocused(bool _focused);

		void SetSize(unsigned int _fontSize);
		inline void SetMaxCharLength(unsigned int _length) { maxCharLength = _length; }
		inline void SetFocusColor(sf::Color _color) { focusColor = _color; }
		inline Text& GetLabel() { return label; }
		inline bool IsFocused() { return isFocused; }

	public:
		std::string text;

	private:
		Text label;
		sf::Color focusColor = sf::Color::White;
		sf::Sprite spriteBackground;
		sf::String placeholder;
		bool isFocused = false;
		bool showBackground = true;
		unsigned int maxCharLength = 100;
	};
}

#endif