#include "StateSelectWorld.h"

#include "StateMainMenu.h"
#include "StateCreateWorld.h"
#include "StateLoading.h"
#include "Common.h"
#include <Stellar/Utils/Utils.h>

#define SAVES_PER_PAGE 4

using namespace Stellar;

void StateSelectWorld::Load()
{
	background.Load();
	spriteMenuBackground = Utils::LoadSprite("UI/SelectCreateWorld/Background.png", true);

	buttonNewGame = ImageButton::Create("UI/SelectCreateWorld/New_Game.png", {});
	buttonTutorial = ImageButton::Create("UI/SelectCreateWorld/New_Game.png", {});
	textNewGame = Text::Create(UI_FONT_MAIN, Language::Get().Translate("selectworld.create"), {});

	std::string tutorial = Language::Get().Translate("selectworld.tutorial");
	std::string upperInput;
	std::transform(tutorial.begin(), tutorial.end(), std::back_inserter(upperInput), ::toupper);
	textTutorial = Text::Create(UI_FONT_MAIN, upperInput, {});
	textNoWorlds = Text::CreateCentered(UI_FONT_MAIN, Language::Get().Translate("selectworld.noworlds"), {});
	textNoWorlds.SetColor(sf::Color(0x909090FF));

	buttonUp = ImageButton::Create("UI/SelectCreateWorld/Up.png", {});
	buttonDown = ImageButton::Create("UI/SelectCreateWorld/Down.png", {});
	buttonBack = MenuButton::Create(UI_FONT_TEXT, "menu.back", {});

	worldPaths.clear();
	saveEntries.clear();
	std::filesystem::create_directories("Saves/Worlds");
	for (std::filesystem::path path : std::filesystem::directory_iterator("Saves/Worlds"))
	{
		if (std::filesystem::exists(path / "Regions") && std::filesystem::exists(path / "settings.bin"))
			saveEntries.emplace_back(SaveEntry::Create(path));
	}
}

void StateSelectWorld::OnResize(sf::Vector2u _size)
{
	sf::Vector2u winSize = Settings::GetWindowSize();
	float scale = Utils::Scale(1.f);

	background.OnResize(_size);

	spriteMenuBackground.setScale({ scale, scale });
	spriteMenuBackground.setPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f });

	buttonNewGame.SetPosition({ _size.x / 2.f, _size.y / 2.f - Utils::Scale(250.f) });
	buttonNewGame.SetScale(scale);
	buttonTutorial.SetPosition({ _size.x / 2.f, _size.y / 2.f - Utils::Scale(337.f) });
	buttonTutorial.SetScale(scale);

	textNewGame.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textNewGame.SetPosition({ _size.x / 2.f - Utils::Scale(220.f), _size.y / 2.f - Utils::Scale(265.f) });
	textTutorial.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textTutorial.SetPosition({ _size.x / 2.f - Utils::Scale(220.f), _size.y / 2.f - Utils::Scale(352.f) });

	textNoWorlds.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textNoWorlds.SetPosition({ _size.x / 2.f, _size.y / 2.f });

	buttonUp.SetPosition({ _size.x / 2.f + Utils::Scale(330.f), _size.y / 2.f + Utils::Scale(120.f) });
	buttonUp.SetScale(scale);
	buttonDown.SetPosition({ _size.x / 2.f + Utils::Scale(330.f), _size.y / 2.f + Utils::Scale(175.f) });
	buttonDown.SetScale(scale);
	buttonBack.SetPosition({ winSize.x - Utils::Scale(125.f), winSize.y - Utils::Scale(50.f) });
	buttonBack.SetSize((unsigned int)(30.f * scale));

	SetEntryPositions();
}

void StateSelectWorld::OnEvent(sf::Event _event)
{
	if (_event.type == sf::Event::TextEntered)
	{
		for (unsigned int i = 0; i < SAVES_PER_PAGE; i++)
		{
			unsigned int index = i + saveIndexOffset;
			if (index >= saveEntries.size())
				continue;

			SaveEntry& entry = saveEntries[index];
			entry.OnTextEntered(_event.text);
		}
	}
}

void StateSelectWorld::OnKeyPressed(sf::Event::KeyEvent _key)
{
	if (_key.code == sf::Keyboard::Escape)
	{
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
		Game::Get().SetState<StateMainMenu>();
	}
}

void StateSelectWorld::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonTutorial.isHovered)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		//std::filesystem::path tutorialCopyPath = "Assets/TutorialWorld";
		std::filesystem::path newPath = "Saves/Worlds/" + Language::Get().Translate("selectworld.tutorial").toAnsiString();

		//if (newPath != tutorialCopyPath)
		//{
		//	while (std::filesystem::exists(newPath) && newPath != tutorialCopyPath)
		//		newPath += "-";
		//}
		//
		//if (newPath == tutorialCopyPath)
		//	return;
		//
		//if (std::filesystem::exists(newPath))
		//	return;
		//
		//std::filesystem::copy(tutorialCopyPath, newPath, std::filesystem::copy_options::recursive);
		std::cout << "Copied Tutorial World to: " << newPath << std::endl;

		Game::Get().SetState<StateLoading>(newPath.filename().string(), 0, false, 0);

		return;
	}
	else if (buttonNewGame.isHovered)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		Game::Get().SetState<StateCreateWorld>();
		return;
	}
	else if (buttonBack.isHovered)
	{
		Game::Get().SetState<StateMainMenu>();
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
		return;
	}

	for (unsigned int i = 0; i < SAVES_PER_PAGE; i++)
	{
		unsigned int index = i + saveIndexOffset;
		if (index >= saveEntries.size())
			continue;

		SaveEntry& entry = saveEntries[index];
		SaveEntryAction action = entry.OnMousePressed(_mouse);

		switch (action)
		{
		case SaveEntryAction::LOAD:
			Game::Get().SetState<StateLoading>(entry.GetPath().filename().string(), 0, false, 0);
			return;

		case SaveEntryAction::EDIT:
		{
			std::filesystem::path newPath = "Saves/Worlds/" + entry.GetNewName();

			if (newPath != entry.GetPath())
			{
				while (std::filesystem::exists(newPath) && newPath != entry.GetPath())
					newPath += "-";
			}
				
			if (newPath == entry.GetPath())
				break;

			try
			{
				std::filesystem::rename(entry.GetPath(), newPath);
				std::cout << "Renamed World from: " << entry.GetPath().filename().string() << " to " << newPath.filename().string() << std::endl;
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				std::cout << "Failed to rename World: " << entry.GetPath() << ": " << e.what() << std::endl;
			}

			// Reload State
			Load();
			OnResize(Settings::GetWindowSize());
			break;
		}

		case SaveEntryAction::DELETE:
			std::filesystem::remove_all(entry.GetPath());
			std::cout << "Deleted World: " << entry.GetPath().filename().string() << std::endl;

			if (saveEntries.size() - 1 == saveIndexOffset && saveIndexOffset > 0)
				saveIndexOffset -= SAVES_PER_PAGE;

			// Reload State
			Load();
			OnResize(Settings::GetWindowSize());
			return;
		}
	}

	if (buttonUp.isHovered && !buttonUp.isDisabled)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		saveIndexOffset -= SAVES_PER_PAGE;
		SetEntryPositions();
	}

	if (buttonDown.isHovered && !buttonDown.isDisabled)
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		saveIndexOffset += SAVES_PER_PAGE;
		SetEntryPositions();
	}
}

void StateSelectWorld::Update(float _deltaTime)
{
	background.Update(_deltaTime);

	spriteMenuBackground.setTexture(AssetManager::GetTexture(
		saveEntries.empty() ? "UI/SelectCreateWorld/Background.png" : "UI/SelectCreateWorld/Background_Worlds.png"));

	buttonNewGame.Update(_deltaTime);
	buttonTutorial.Update(_deltaTime);
	buttonBack.Update(_deltaTime);

	if (!buttonUp.isDisabled)
		buttonUp.Update(_deltaTime);

	if (!buttonDown.isDisabled)
		buttonDown.Update(_deltaTime);

	for (unsigned int i = 0; i < SAVES_PER_PAGE; i++)
	{
		unsigned int index = i + saveIndexOffset;
		if (index >= saveEntries.size())
			continue;

		SaveEntry& entry = saveEntries[index];
		entry.Update(_deltaTime);
	}

	buttonUp.isDisabled = saveIndexOffset == 0;
	buttonDown.isDisabled = saveIndexOffset + SAVES_PER_PAGE >= saveEntries.size();
}


void StateSelectWorld::Draw(sf::RenderTexture& _texture)
{
	background.Draw(_texture);
	_texture.draw(spriteMenuBackground);

	buttonNewGame.Draw(_texture);
	textNewGame.Draw(_texture);
	buttonTutorial.Draw(_texture);
	textTutorial.Draw(_texture);
	buttonBack.Draw(_texture);

	if (!buttonUp.isDisabled)
		buttonUp.Draw(_texture);

	if (!buttonDown.isDisabled)
		buttonDown.Draw(_texture);

	for (unsigned int i = 0; i < SAVES_PER_PAGE; i++)
	{
		unsigned int index = i + saveIndexOffset;
		if (index >= saveEntries.size())
			continue;

		SaveEntry& entry = saveEntries[index];
		entry.Draw(_texture);
	}

	if (saveEntries.empty())
		textNoWorlds.Draw(_texture);
}

void StateSelectWorld::SetEntryPositions()
{
	sf::Vector2u winSize = Settings::GetWindowSize();
	float scale = Utils::Scale(1.f);
	for (unsigned int i = 0; i < SAVES_PER_PAGE; i++)
	{
		unsigned int index = i + saveIndexOffset;
		if (index >= saveEntries.size())
			continue;

		SaveEntry& entry = saveEntries[index];
		entry.SetScale(scale);
		entry.SetPosition({ winSize.x / 2.f - Utils::Scale(65.f), winSize.y / 2.f - Utils::Scale(143.f) + i * Utils::Scale(95.f) });
	}
}
