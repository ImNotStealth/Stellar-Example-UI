#include "Text.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Utils/Utils.h"

namespace Stellar {

	Text Text::Create(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize)
	{
		Text obj;
		obj.frontText.setFont(AssetManager::GetFont(_fontPath));
		obj.frontText.setFillColor(sf::Color::White);
		obj.frontText.setCharacterSize(_fontSize);
		obj.frontText.setString(_content);
		obj.SetPosition(_pos);
		obj.isCentered = false;
		return obj;
	}

	Text Text::CreateCentered(const std::filesystem::path& _fontPath, const sf::String& _content, sf::Vector2f _pos, unsigned int _fontSize)
	{
		Text obj = Create(_fontPath, _content, _pos, _fontSize);
		obj.Center();

		return obj;
	}

	void Text::Center()
	{
		isCentered = true;
		sf::FloatRect bounds = frontText.getLocalBounds();
		frontText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	}

	void Text::SetCharacterSize(unsigned int _fontSize)
	{
		frontText.setCharacterSize(_fontSize);
		fontSize = (float)_fontSize;
		if (isCentered)
		{
			Center();
		}
		SetPosition(frontText.getPosition());
	}

	void Text::SetPosition(sf::Vector2f _pos)
	{
		pos = _pos;
		frontText.setPosition(_pos);
	}

	void Text::Move(sf::Vector2f _pos)
	{
		pos += _pos;
		frontText.move(_pos);
	}

	void Text::SetString(const sf::String& _content)
	{
		frontText.setString(_content);
		if (isCentered)
		{
			Center();
		}
	}

	void Text::SetColor(sf::Color _color)
	{
		color = _color;
	}

	void Text::Draw(sf::RenderTexture& _texture)
	{
		frontText.setPosition({ pos.x + (fontSize / 10.f), pos.y + (fontSize / 10.f) });
		frontText.setFillColor(sf::Color(0x000000AA));
		_texture.draw(frontText);

		frontText.setPosition(pos);
		frontText.setFillColor(color);
		_texture.draw(frontText);
	}
}