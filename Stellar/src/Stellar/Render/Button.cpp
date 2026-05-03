#include "Button.h"
#include "Stellar/Core/Language.h"
#include "Stellar/Core/Game.h"
#include "Stellar/Utils/Utils.h"

namespace Stellar {

	Button Button::Create(const std::filesystem::path& _fontPath, const std::string& _langKey, sf::Vector2f _pos, unsigned int _fontSize)
	{
		Button button;
		button.label = Text::CreateCentered(_fontPath, Language::Get().Translate(_langKey), _pos, _fontSize);
		button.easing = Easing(EasingType::OUT_CIRC, 0.25f, 1.f, 1.25f);

		button.easing.ResetAndFlip(); // Otherwise hover in & out will be flipped in Update();
		button.pos = _pos;

		return button;
	}

	void Button::Update(float _deltaTime)
	{
		sf::FloatRect buttonBounds = label.frontText.getGlobalBounds();
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
			label.Center();
		}

		if (easing.IsFinished())
		{
			updateEasing = false;
		}

		lastHovered = isHovered;
	}

	void Button::Draw(sf::RenderTexture& _rt)
	{
		label.Draw(_rt);
	}

	void Button::SetPosition(sf::Vector2f _pos)
	{
		label.SetPosition(_pos);
		pos = _pos;
	}

	void Button::SetSize(unsigned int _fontSize)
	{
		label.SetCharacterSize(_fontSize);
	}
}