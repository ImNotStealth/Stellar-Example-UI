#include "StateMainMenu.h"

#include "Common.h"
#include "StateTest.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

bool StateMainMenu::firstOpen = true;

void StateMainMenu::Load()
{
	spriteLogo = Utils::LoadSprite("UI/Game.png", true);

	buttonPlay = Button::Create(UI_FONT_MAIN, "mainmenu.play", {});
	buttonSettings = Button::Create(UI_FONT_MAIN, "mainmenu.settings", {});
	buttonQuit = Button::Create(UI_FONT_MAIN, "mainmenu.quit", {});

	textExample = Text::Create(UI_FONT_TEXT, Language::Get().Translate("mainmenu.example"), {});
	paragraphExample = Paragraph::Create(UI_FONT_TEXT, Language::Get().Translate("mainmenu.paragraphExample"), {});

	checkbox = Checkbox::Create(CHECKBOX_TEXTURE, {});

	imageButton = ImageButton::Create("UI/Audio.png", {});

	if (firstOpen)
	{
		easeFadeIn = Easing(EasingType::IN_QUINT, 1.f, 255.f, 0.f);
		shapeFadeIn.setFillColor(sf::Color::Black);
	}
}

void StateMainMenu::OnResize(sf::Vector2u _size)
{
	float scale = Utils::Scale(1.f);

	spriteLogo.setScale({ 0.6f * scale, 0.6f * scale });
	spriteLogo.setPosition({ (float)_size.x / 2.f, (float)_size.y / 4.f});

	textExample.SetCharacterSize((unsigned int)(15.f * scale));
	textExample.SetPosition({ 7.f * scale, _size.y - 25.f * scale });

	paragraphExample.SetCharacterSize((unsigned int)(30.f * scale));
	paragraphExample.SetPosition({ 20.f * scale, 20.f * scale });

	float spacing = Utils::Scale(48.f);
	unsigned int buttonSize = (unsigned int)(30.f * scale);
	buttonPlay.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f - spacing});
	buttonPlay.SetSize((unsigned int)(40.f * scale));

	buttonSettings.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f });
	buttonSettings.SetSize((unsigned int)(30.f * scale));

	buttonQuit.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f + spacing * 2.f });
	buttonQuit.SetSize((unsigned int)(30.f * scale));

	checkbox.SetScale(scale * 0.25f);
	checkbox.SetPosition({ (float)_size.x / 4.f, (float)_size.y / 2.f });

	imageButton.SetScale(scale * 0.25f);
	imageButton.SetPosition({ (float)_size.x / 3.f, (float)_size.y / 2.f });

	if (firstOpen)
	{
		shapeFadeIn.setSize({ (float)_size.x, (float)_size.y });
	}
}

void StateMainMenu::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonPlay.isHovered)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		Game::Get().SetState<StateTest>();
		return;
	}
	else if (buttonSettings.isHovered)
	{
		std::cout << "Settings pressed!" << std::endl;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonQuit.isHovered)
	{
		std::cout << "Quit pressed!" << std::endl;
		Game::Get().GetRenderWindow().close();
	}
	else if (checkbox.IsHovered())
	{
		checkbox.Toggle();
		std::cout << "Checkbox toggled: " << checkbox.IsToggled() << std::endl;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (imageButton.isHovered)
	{
		std::cout << "ImageButton pressed!" << std::endl;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
}

void StateMainMenu::Update(float _deltaTime)
{
	buttonPlay.Update(_deltaTime);
	buttonSettings.Update(_deltaTime);
	buttonQuit.Update(_deltaTime);
	checkbox.Update(_deltaTime);
	imageButton.Update(_deltaTime);

	if (firstOpen)
	{
		if (!easeFadeIn.IsFinished())
		{
			easeFadeIn.Update(_deltaTime);
			shapeFadeIn.setFillColor(sf::Color(0, 0, 0, (unsigned int)easeFadeIn.value));
		}
		else
		{
			firstOpen = false;
		}
	}
}

void StateMainMenu::Draw(sf::RenderTexture& _texture)
{
	_texture.draw(spriteLogo);
	textExample.Draw(_texture);
	paragraphExample.Draw(_texture);

	buttonPlay.Draw(_texture);
	buttonSettings.Draw(_texture);
	buttonQuit.Draw(_texture);
	checkbox.Draw(_texture);
	imageButton.Draw(_texture);

	if (firstOpen && !easeFadeIn.IsFinished())
	{
		_texture.draw(shapeFadeIn);
	}
}
