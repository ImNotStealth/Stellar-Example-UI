#include "MenuButton.h"
#include "Stellar/Core/Language.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Core/Game.h"
#include "Stellar/Utils/Utils.h"

namespace Stellar {

	MenuButton MenuButton::Create(const std::filesystem::path& _fontPath, const std::string& _langKey, sf::Vector2f _pos, unsigned int _fontSize)
	{
		return Create(_fontPath, "UI/Settings/Button_Background.png", _langKey, _pos, _fontSize);
	}

	MenuButton MenuButton::Create(const std::filesystem::path& _fontPath, const std::filesystem::path& _spritePath, const std::string& _langKey, sf::Vector2f _pos, unsigned int _fontSize)
	{
		MenuButton button;
		button.label = Text::CreateCentered(_fontPath, Language::Get().Translate(_langKey), _pos, _fontSize);
		button.easing = Easing(EasingType::OUT_CIRC, 0.25f, 1.f, 1.1f);

		button.spriteBG.setTexture(AssetManager::GetTexture(_spritePath));
		button.spriteBG.setScale({ (float)_fontSize / 30.f, (float)_fontSize / 30.f });

		sf::FloatRect bounds = button.spriteBG.getLocalBounds();
		button.spriteBG.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });
		button.spriteBG.setPosition(_pos);

		button.easing.ResetAndFlip(); // Otherwise hover in & out will be flipped in Update();
		button.pos = _pos;

		return button;
	}

	void MenuButton::Update(float _deltaTime)
	{
		sf::FloatRect buttonBounds = spriteBG.getGlobalBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Get().GetRenderWindow());
		isHovered = buttonBounds.contains((float)mousePos.x, (float)mousePos.y);

		if (isHovered != lastHovered)
		{
			Utils::SetCursor(isDisabled && isHovered ? sf::Cursor::Type::NotAllowed : isHovered ? sf::Cursor::Type::Hand : sf::Cursor::Type::Arrow);
			easing.ResetAndFlip();
			updateEasing = true;
		}

		if (!easing.IsFinished() && !isDisabled && updateEasing)
		{
			easing.Update(_deltaTime);
			label.frontText.setScale({ easing.value, easing.value });
			spriteBG.setScale({ scale / 1.5f * easing.value, scale / 1.5f * easing.value });
			label.Center();
		}

		if (easing.IsFinished())
		{
			updateEasing = false;
		}

		lastHovered = isHovered;
	}

	void MenuButton::Draw(sf::RenderTexture& _rt)
	{
		_rt.draw(spriteBG);
		label.Draw(_rt);
	}

	void MenuButton::SetPosition(sf::Vector2f _pos)
	{
		label.SetPosition(_pos);
		spriteBG.setPosition(_pos);
		pos = _pos;
	}

	void MenuButton::SetSize(unsigned int _fontSize)
	{
		scale = _fontSize / 30.f;

		label.SetCharacterSize(_fontSize);
		spriteBG.setScale({ scale / 1.5f, scale / 1.5f });

		sf::FloatRect bounds = spriteBG.getLocalBounds();
		spriteBG.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });

	}
}