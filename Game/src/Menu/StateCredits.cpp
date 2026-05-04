#include "StateCredits.h"

#include "Common.h"
#include "StateMainMenu.h"
#include <Stellar/Utils/Utils.h>

#define CREDITS_TIMER 3.f
#define CREDITS_MOVE_Y 75.f

using namespace Stellar;

void StateCredits::Load()
{
	sf::Vector2f winSize = Game::Get().GetRenderWindow().getView().getSize();

	spriteBackground.setTexture(AssetManager::GetTexture("UI/Background.png"));

	spriteLogo.setTexture(AssetManager::GetTexture("UI/Game.png"));
	sf::FloatRect logoBounds = spriteLogo.getLocalBounds();
	spriteLogo.setOrigin({ logoBounds.width / 2.f, logoBounds.height / 2.f });
	spriteLogo.setPosition({ winSize.x / 2.f, winSize.y / 2.f });

	beginTimer = CREDITS_TIMER;
	endTimer = CREDITS_TIMER;
	startedEndFade = false;
	
	std::string filePath = std::format("Assets/Lang/Credits-{}.lang", Language::LangEnumToStr(Settings::Get().language));
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return;
	}

	credits.clear();
	std::string line;
	unsigned int lineIndex = 0;
	while (std::getline(file, line))
	{
		// Trim leading and trailing spaces
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		sf::String str = sf::String::fromUtf8(line.begin(), line.end());
		credits.push_back(Text::CreateCentered(UI_FONT_TEXT, str, {}));
	}

	easeFade = Easing(EasingType::IN_QUINT, 0.5f, 255.f, 0.f);
	shapeFade.setFillColor(sf::Color::Black);
	shapeFade.setSize(winSize);
}

void StateCredits::OnResize(sf::Vector2u _size)
{
	sf::Vector2u winSize = Settings::GetWindowSize();
	sf::Vector2u backgroundTexSize = spriteBackground.getTexture()->getSize();
	spriteBackground.setOrigin({ (float)backgroundTexSize.x / 2.f, (float)backgroundTexSize.y / 2.f });
	float scaleX = (float)winSize.x / (float)backgroundTexSize.x;
	float scaleY = (float)winSize.y / (float)backgroundTexSize.y;
	float bgScale = std::max(scaleX, scaleY);
	spriteBackground.setScale({ bgScale, bgScale });
	spriteBackground.setPosition({ winSize.x / 2.f, winSize.y / 2.f });

	float scale = Utils::Scale(1.f);
	spriteLogo.setScale({ 0.8f * scale, 0.8f * scale });
	spriteLogo.setPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f + totalOffset * scale });

	for (unsigned int i = 0; i < credits.size(); i++)
	{
		Text& text = credits[i];

		std::string line = text.frontText.getString();

		bool isTitle = line.find("-- ") == 0 && line.rfind(" --") == (line.size() - 3);
		bool isSubtitle = line.find("- ") == 0 && line.rfind(" -") == (line.size() - 2);
		bool isBold = isTitle || isSubtitle;

		text.SetPosition({ _size.x / 2.f, _size.y + 15.f + i * scale * 30.f + totalOffset * scale });
		text.SetCharacterSize((unsigned int)((isBold ? 30.f : 26.f) * scale));
	}

	shapeFade.setSize({ (float)_size.x, (float)_size.y });
}

void StateCredits::OnKeyPressed(sf::Event::KeyEvent _key)
{
	if (_key.code != sf::Keyboard::F11)
	{
		StateMainMenu::firstOpen = true;
		Game::Get().SetState<StateMainMenu>();
	}
}

void StateCredits::Update(float _deltaTime)
{
	float scale = Utils::Scale(1.f);
	sf::Vector2f winSize = Game::Get().GetRenderWindow().getView().getSize();
	bool creditsEnded = credits.back().frontText.getPosition().y < winSize.y / 2.f;

	if (!easeFade.IsFinished())
	{
		easeFade.Update(_deltaTime);
		shapeFade.setFillColor(sf::Color(0, 0, 0, (unsigned int)easeFade.value));
	}

	if (creditsEnded)
	{
		if (endTimer > 0.f)
		{
			endTimer -= _deltaTime;
		}
		else if (endTimer <= 0.f && easeFade.IsFinished() && !startedEndFade)
		{
			easeFade.ResetAndFlip();
			startedEndFade = true;
		}
		else if (easeFade.IsFinished())
		{
			StateMainMenu::firstOpen = true;
			Game::Get().SetState<StateMainMenu>();
			return;
		}
	}

	if (beginTimer > 0.f)
	{
		beginTimer -= _deltaTime;
	}

	if (beginTimer <= 0.f && !creditsEnded)
	{
		totalOffset += -CREDITS_MOVE_Y * _deltaTime;
		sf::Vector2f offset = { 0.f, -CREDITS_MOVE_Y * scale * _deltaTime };
		spriteLogo.move(offset);
		for (Text& text : credits)
		{
			text.Move(offset);
		}
	}
}

void StateCredits::Draw(sf::RenderTexture& _texture)
{
	_texture.draw(spriteBackground);

	_texture.draw(spriteLogo);

	for (Text& text : credits)
	{
		text.Draw(_texture);
	}

	if (!easeFade.IsFinished())
	{
		_texture.draw(shapeFade);
	}
}
