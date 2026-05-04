#include "CategoryButton.h"

#include <Stellar/Core/AssetManager.h>
#include <Stellar/Core/Game.h>
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

CategoryButton CategoryButton::Create(const std::filesystem::path& _fontPath, const std::filesystem::path& _texturePath, std::string _labelKey, sf::Vector2f _pos, float _scale)
{
	CategoryButton button;
	button.spriteBG.setTexture(AssetManager::GetTexture("UI/Settings/Category.png"));
	button.spriteIcon.setTexture(AssetManager::GetTexture(_texturePath));
	button.text = Text::Create(_fontPath, Language::Get().Translate(_labelKey), {});
	button.easing = Easing(EasingType::OUT_CIRC, 0.25f, 0.f, 50.f);
	button.easing.ResetAndFlip(); // Otherwise hover in & out will be flipped in Update();

	button.SetScale(_scale);
	button.SetPosition(_pos);
	return button;
}

void CategoryButton::Update(float _deltaTime)
{
	sf::FloatRect buttonBounds = spriteBG.getGlobalBounds();
	sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Get().GetRenderWindow());
	sf::Vector2f scaledMousePos = Game::Get().GetRenderWindow().mapPixelToCoords(mousePos);
	isHovered = buttonBounds.contains(scaledMousePos.x, scaledMousePos.y);

	if (isHovered != lastHovered)
	{
		Utils::SetCursor(isDisabled && isHovered ? sf::Cursor::Type::NotAllowed : isHovered ? sf::Cursor::Type::Hand : sf::Cursor::Type::Arrow);
		easing.ResetAndFlip();
		updateEasing = true;
	}

	if (!easing.IsFinished() && !isDisabled && updateEasing)
	{
		easing.Update(_deltaTime);
		spriteBG.setPosition({ pos.x + Utils::Scale(easing.value), pos.y });
		spriteIcon.setPosition({ pos.x + Utils::Scale(8.f) + Utils::Scale(easing.value), pos.y });
		text.SetPosition({ pos.x + Utils::Scale(85.f) + Utils::Scale(easing.value), pos.y - Utils::Scale(3.f) });
	}

	if (easing.IsFinished())
	{
		updateEasing = false;
	}

	lastHovered = isHovered;
}

void CategoryButton::Draw(sf::RenderTexture& _rt)
{
	_rt.draw(spriteBG);
	_rt.draw(spriteIcon);
	text.Draw(_rt);
}

void CategoryButton::SetPosition(sf::Vector2f _pos)
{
	pos = _pos;
	spriteBG.setPosition(_pos);
	spriteIcon.setPosition({ _pos.x + Utils::Scale(8.f) , _pos.y });
	text.SetPosition({ _pos.x + Utils::Scale(85.f), _pos.y - Utils::Scale(3.f) });
}

void CategoryButton::SetScale(float _scale)
{
	scale = _scale;
	spriteBG.setScale({ scale, scale });
	spriteIcon.setScale({ scale * 0.35f, scale * 0.35f });
	text.SetCharacterSize((unsigned int)(30.f * scale));

	sf::FloatRect boundsBG = spriteBG.getLocalBounds();
	spriteBG.setOrigin({ 0.f, boundsBG.height / 2.f });
	spriteIcon.setOrigin({ 0.f, spriteIcon.getLocalBounds().height / 2.f });
	text.frontText.setOrigin({ 0.f, text.frontText.getLocalBounds().height / 2.f });
}