#include "Textbox.h"

#include "Stellar/Core/Language.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Utils/Utils.h"

namespace Stellar
{
	Textbox Textbox::Create(const std::filesystem::path& _fontPath, const std::string& _langPlaceholderKey, sf::Vector2f _pos, bool _bg, unsigned int _fontSize)
	{
		Textbox textbox;
		textbox.placeholder = Language::Get().Translate(_langPlaceholderKey);
		textbox.label = Text::Create(_fontPath, textbox.placeholder, _pos, _fontSize);
		textbox.spriteBackground.setTexture(AssetManager::GetTexture("UI/SelectCreateWorld/Input_Background.png"));
		textbox.spriteBackground.setScale({ (float)_fontSize / 25.f, (float)_fontSize / 25.f });
		textbox.showBackground = _bg;
		return textbox;
	}

	Textbox Textbox::CreateCentered(const std::filesystem::path& _fontPath, const std::string& _langPlaceholderKey, sf::Vector2f _pos, bool _bg, unsigned int _fontSize)
	{
		Textbox textbox;
		textbox.placeholder = Language::Get().Translate(_langPlaceholderKey);
		textbox.label = Text::CreateCentered(_fontPath, textbox.placeholder, _pos, _fontSize);
		textbox.spriteBackground.setTexture(AssetManager::GetTexture("UI/SelectCreateWorld/Input_Background.png"));
		textbox.spriteBackground.setScale({ (float)_fontSize / 25.f, (float)_fontSize / 25.f });
		textbox.showBackground = _bg;
		return textbox;
	}

	void Textbox::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
	{
		sf::FloatRect bounds = spriteBackground.getGlobalBounds();
		isFocused = bounds.contains({ (float)_mouse.x, (float)_mouse.y });
	}

	void Textbox::OnTextEntered(sf::Event::TextEvent _text)
	{
		if (!isFocused)
			return;

        // If I'm honest Claude did this most of this, I don't understand this hexadecimal BS -\_(o_O)_/-
		
        uint32_t unicode = _text.unicode;

        if (unicode == '\b') // Backspace
        {
            if (!text.empty())
            {
                text.pop_back();
                if (text.empty())
                {
                    label.SetString(placeholder);
                }
                else
                {
                    label.SetString(text);
                }
            }
        }
        else if (unicode == 127 ||                      // DEL key
            (unicode >= 0x0001 && unicode <= 0x001F) || // Control characters
            (unicode >= 0x007F && unicode <= 0x009F) || // Extended control chars
            (unicode >= 0x2000 && unicode <= 0x200F) || // Various spaces and direction marks
            (unicode >= 0x2028 && unicode <= 0x202F) || // Separators and direction marks
            (unicode >= 0xE000 && unicode <= 0xF8FF) || // Private use area
            (unicode >= 0xFFF0 && unicode <= 0xFFFF))   // Special Unicode characters
        {
            return;
        }
        else if (unicode >= 32) // Characters above ASCII 32 (Space)
        {
            // This is to prevent the player from using the world name as a directory or smth along those lines
            if (unicode == '\\' || unicode == '/')
            {
                return;
            }

            char character = static_cast<char>(unicode);

            // For accented and other special characters that fit in a single byte
            if (unicode <= 0xFF)
            {
                if (std::string(text + character).size() <= maxCharLength)
                {
                    text += character;
                    label.SetString(text);
                }
            }
            // For characters that SFML sends as a single unicode value (like accented chars)
            // but actually need UTF-8 multi-byte encoding
            else
            {
                // Let SFML handle conversion through sf::String
                sf::String unicodeStr;
                unicodeStr += static_cast<sf::Uint32>(unicode);
                if ((text.size() + 1) <= maxCharLength)
                {
                    text += unicode;
                    label.SetString(text);
                }
            }
        }
	}

	void Textbox::Draw(sf::RenderTexture& _rt)
	{
		if (showBackground)
			_rt.draw(spriteBackground);
		label.SetColor(isFocused ? focusColor : sf::Color(0x909090AA));
		label.Draw(_rt);
	}

	void Textbox::SetPosition(sf::Vector2f _pos)
	{
		label.SetPosition(_pos);
		spriteBackground.setPosition({ _pos.x - Utils::Scale(10.f), _pos.y - Utils::Scale(7.f) });
	}

	void Textbox::SetLabelContent(const std::string& _placeholderKey)
	{
		label.SetString(Language::Get().Translate(_placeholderKey));
	}

	void Textbox::SetFocused(bool _focused)
	{
		isFocused = _focused;
	}

	void Textbox::SetSize(unsigned int _fontSize)
	{
		label.SetCharacterSize(_fontSize);
		spriteBackground.setScale({ (float)_fontSize / 30.f, (float)_fontSize / 30.f });
	}
}