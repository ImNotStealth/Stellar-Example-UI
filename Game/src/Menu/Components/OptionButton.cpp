#include "OptionButton.h"

#include <Stellar/Core/Language.h>
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

OptionButton OptionButton::Create(const std::filesystem::path& _fontPath, std::vector<std::string> _options, unsigned int _defaultIndex, sf::Vector2f _pos, unsigned int _fontSize)
{
	OptionButton button;
	button.label = Text::Create(_fontPath, Language::Get().Translate(_options.at(_defaultIndex)), {});
	button.buttonLeft = Button::Create("Fonts/RenegadePursuit.ttf", "<", {}, _fontSize);
	button.buttonRight = Button::Create("Fonts/RenegadePursuit.ttf", ">", {}, _fontSize);
	button.options = _options;
	button.selectedIndex = _defaultIndex;
	button.SetPosition(_pos);
	return button;
}

bool OptionButton::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonLeft.isHovered)
	{
		selectedIndex = selectedIndex == 0 ? (unsigned int)options.size() - 1 : selectedIndex - 1;
		label.SetString(Language::Get().Translate(options.at(selectedIndex)));
		SetPosition(pos);
		return true;
	}
	else if (buttonRight.isHovered)
	{
		selectedIndex = (selectedIndex + 1) % (unsigned int)options.size();
		label.SetString(Language::Get().Translate(options.at(selectedIndex)));
		SetPosition(pos);
		return true;
	}

	return false;
}

void OptionButton::Update(float _deltaTime)
{
	buttonLeft.Update(_deltaTime);
	buttonRight.Update(_deltaTime);
}

void OptionButton::Draw(sf::RenderTexture& _rt)
{
	label.Draw(_rt);
	buttonLeft.Draw(_rt);
	buttonRight.Draw(_rt);
}

void OptionButton::SetPosition(sf::Vector2f _pos)
{
	label.SetPosition({ _pos.x + Utils::Scale(20.f), _pos.y });
	buttonLeft.label.SetPosition({ _pos.x, _pos.y + label.fontSize / 2.f });
	buttonRight.label.SetPosition({ _pos.x + label.frontText.getLocalBounds().width + Utils::Scale(40.f), _pos.y + label.fontSize / 2.f });
	pos = _pos;
}

void OptionButton::SetSize(unsigned int _fontSize)
{
	label.SetCharacterSize(_fontSize);
	buttonLeft.SetSize(_fontSize);
	buttonRight.SetSize(_fontSize);
	SetPosition(pos);
}