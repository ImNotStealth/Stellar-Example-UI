#include "StateLoading.h"

#include <Stellar/Utils/Utils.h>
#include "Common.h"
#include "Menu/StateAsyncExample.h"

#define TIME_MSG_1 30.f
#define TIME_MSG_2 120.f
#define TIME_MSG_3 180.f
#define THROBBER_COUNT 6

using namespace Stellar;

void StateLoading::Load()
{
	background.Load();

	textStatus = std::make_unique<sf::Text>(sf::Text(Language::Get().Translate("loading.loading"), AssetManager::GetFont(UI_FONT_TEXT)));

	for (unsigned int i = 0; i < THROBBER_COUNT; i++)
	{
		std::shared_ptr<LoadingThrobber> throbber = std::make_shared<LoadingThrobber>();
		throbber->sprite = Utils::LoadSprite("UI/Grass.png", false);
		throbber->easing = Easing(EasingType::IN_OUT_ELASTIC, 0.75f, 0.f, 1.f);

		throbbers.push_back(throbber);
	}

	Game::Get().SetStateAsync<StateAsyncExample>();
}

void StateLoading::OnResize(sf::Vector2u _size)
{
	sf::Vector2u winSize = Settings::GetWindowSize();
	float scale = Utils::Scale(1.f);

	background.OnResize(_size);

	textStatusPos = { (float)_size.x / 2.f, (float)_size.y / 2.f + 100.f * scale };
	//textStatus->setCharacterSize((unsigned int)(30.f * scale));
	if (textStatus)
	{
		textStatus->setScale({ scale, scale });
		textStatus->setPosition(textStatusPos);
	}

	// Throbber stuff
	for (auto& throbber : throbbers) {
		throbber->sprite.setScale({ scale / 2.f, scale / 2.f });
	}

	float baseWidth = throbbers[0]->sprite.getGlobalBounds().width;
	float spacing = Utils::Scale(20.f);
	float totalWidth = throbbers.size() * (baseWidth + spacing) - spacing;
	sf::Vector2f center = { (float)_size.x / 2.f, (float)_size.y / 2.f };
	sf::Vector2f startPos = { center.x - totalWidth / 2.f, center.y };

	for (unsigned int i = 0; i < throbbers.size(); i++)
	{
		auto& throbber = throbbers[i];
		throbber->pos = startPos + sf::Vector2f(i * (baseWidth + spacing), 0.f);
	}
}

void StateLoading::Update(float _deltaTime)
{
	background.Update(_deltaTime);

	if (!resetting)
	{
		// Normal forward update, one by one
		for (size_t i = 0; i < throbbers.size(); ++i)
		{
			if (i == 0 || throbbers[i - 1]->easing.IsFinished())
			{
				throbbers[i]->easing.Update(_deltaTime);
			}
		}

		// Check if all are finished to begin reset phase
		bool allFinished = std::all_of(throbbers.begin(), throbbers.end(), [](const auto& t)
		{
			return t->easing.IsFinished();
		});

		if (allFinished)
		{
			resetting = true;
			resettingIndex = 0;
			throbbers[0]->easing.ResetAndFlip(); // Start reset wave
		}
	}
	else
	{
		// Resetting phase, update only the current resetting one
		throbbers[resettingIndex]->easing.Update(_deltaTime);

		if (throbbers[resettingIndex]->easing.IsFinished())
		{
			resettingIndex++;
			if (resettingIndex < throbbers.size())
			{
				throbbers[resettingIndex]->easing.ResetAndFlip();
			}
			else
			{
				resetting = false; // Done resetting, loop back to update phase
			}
		}
	}

	if (statusTime < TIME_MSG_3)
	{
		statusTime += _deltaTime;
		if (statusTime >= TIME_MSG_3 && textStatus)
		{
			textStatus->setString(Language::Get().Translate("loading.verylongtime"));
		}
		else if (statusTime >= TIME_MSG_2 && textStatus)
		{
			textStatus->setString(Language::Get().Translate("loading.longtime"));
		}
		else if (statusTime >= TIME_MSG_1 && textStatus)
		{
			textStatus->setString(Language::Get().Translate("loading.sometime"));
		}
	}
}

void StateLoading::Draw(sf::RenderTexture& _texture)
{
	background.Draw(_texture);

	// Status text bullshit
	
	if (textStatus)
	{
		sf::FloatRect bounds = textStatus->getLocalBounds();
		float fontSize = 30.f * Utils::Scale(1.f);
		textStatus->setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		textStatus->setPosition({ textStatusPos.x + (fontSize / 10.f), textStatusPos.y + (fontSize / 10.f) });
		textStatus->setFillColor(sf::Color(0x000000AA));
		_texture.draw(*textStatus);
		textStatus->setPosition(textStatusPos);
		textStatus->setFillColor(sf::Color::White);
		_texture.draw(*textStatus);
	}

	for (auto& throbber : throbbers)
	{
		if (!throbber)
			continue;
		throbber->sprite.setPosition({ throbber->pos.x, throbber->pos.y - throbber->easing.value * Utils::Scale(64.f) });
		_texture.draw(throbber->sprite);
	}
}

void StateLoading::SetLoadState(std::string _msg)
{
	if (textStatus)
	{
		textStatus->setString(Language::Get().Translate(_msg));
		statusTime = 0.f;
	}
}
