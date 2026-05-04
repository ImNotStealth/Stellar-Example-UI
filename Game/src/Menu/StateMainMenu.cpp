#include "StateMainMenu.h"

#include "StateSelectWorld.h"
#include "StateSettings.h"
#include "Common.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

bool StateMainMenu::firstOpen = true;

void StateMainMenu::Load()
{
	background.Load();

	spriteLogo = Utils::LoadSprite("UI/Game.png", true);

	buttonPlay = Button::Create(UI_FONT_MAIN, "mainmenu.play", {});
	buttonSettings = Button::Create(UI_FONT_MAIN, "mainmenu.settings", {});
	buttonQuit = Button::Create(UI_FONT_MAIN, "mainmenu.quit", {});

	textCopyright = Text::Create(UI_FONT_MAIN, Language::Get().Translate("copyright"), {});

	if (firstOpen)
	{
		easeFadeIn = Easing(EasingType::IN_QUINT, 0.5f, 255.f, 0.f);
		shapeFadeIn.setFillColor(sf::Color::Black);
	}
}

void StateMainMenu::OnResize(sf::Vector2u _size)
{
	background.OnResize(_size);

	float scale = Utils::Scale(1.f);

	spriteLogo.setScale({ 0.6f * scale, 0.6f * scale });
	spriteLogo.setPosition({ (float)_size.x / 2.f, (float)_size.y / 4.f});

	textCopyright.SetCharacterSize((unsigned int)(15.f * scale));
	textCopyright.SetPosition({ 7.f * scale, _size.y - 25.f * scale });

	float spacing = Utils::Scale(48.f);
	unsigned int buttonSize = (unsigned int)(30.f * scale);
	buttonPlay.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f - spacing});
	buttonPlay.SetSize((unsigned int)(40.f * scale));

	buttonSettings.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f });
	buttonSettings.SetSize((unsigned int)(30.f * scale));

	buttonQuit.SetPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f + spacing * 2.f });
	buttonQuit.SetSize((unsigned int)(30.f * scale));

	if (firstOpen)
	{
		shapeFadeIn.setSize({ (float)_size.x, (float)_size.y });
	}
}

void StateMainMenu::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonPlay.isHovered)
	{
		Game::Get().SetState<StateSelectWorld>();
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonSettings.isHovered)
	{
		Game::Get().SetState<StateSettings>();
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonQuit.isHovered)
	{
		Game::Get().GetRenderWindow().close();
	}
}

void StateMainMenu::Update(float _deltaTime)
{
	background.Update(_deltaTime);

	buttonPlay.Update(_deltaTime);
	buttonSettings.Update(_deltaTime);
	buttonQuit.Update(_deltaTime);

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
	background.Draw(_texture);

	_texture.draw(spriteLogo);
	textCopyright.Draw(_texture);

	buttonPlay.Draw(_texture);
	buttonSettings.Draw(_texture);
	buttonQuit.Draw(_texture);

	if (firstOpen && !easeFadeIn.IsFinished())
	{
		_texture.draw(shapeFadeIn);
	}
}
