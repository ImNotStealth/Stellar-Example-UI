#include "StateCreateWorld.h"

#include "StateSelectWorld.h"
#include "StateLoading.h"
#include "Common.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

void StateCreateWorld::Load()
{
	background.Load();
	spriteMenuBackground = Utils::LoadSprite("UI/SelectCreateWorld/Background.png", true);
	spriteCreatingWorld = Utils::LoadSprite("UI/SelectCreateWorld/New_Game.png", true);

	textCreatingWorld = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.creating"), {});
	textWorldName = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.name"), {});
	textWorldNameTip = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.name.tip"), {});
	textWorldNameTip.SetColor(sf::Color(0x909090FF));
	textSeed = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.seed"), {});
	textSeedTip = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.seed.tip"), {});
	textSeedTip.SetColor(sf::Color(0x909090FF));
	textSize = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.size"), {});
	textBonusChest = Text::Create(UI_FONT_MAIN, Language::Get().Translate("createworld.bonuschest"), {});

	inputWorldName = Textbox::Create(UI_FONT_TEXT, "createworld.name.default", {});
	inputWorldName.SetMaxCharLength(16);
	//inputWorldName.text = Language::Get().Translate("createworld.name.default");
	inputSeed = Textbox::Create(UI_FONT_TEXT, "createworld.seed.default", {});
	inputSeed.SetMaxCharLength(16);
	optionSize = OptionButton::Create(UI_FONT_TEXT, { "createworld.size.small", "createworld.size.medium", "createworld.size.large", "createworld.size.giant" }, 1, {});
	checkboxBonusChest = Checkbox::Create(CHECKBOX_TEXTURE, {}, 0.75f, false);
	buttonCreate = MenuButton::Create(UI_FONT_MAIN, "UI/SelectCreateWorld/Create.png", "createworld.create", {});
	buttonCancel = MenuButton::Create(UI_FONT_MAIN, "UI/SelectCreateWorld/Cancel.png", "createworld.cancel", {});

	CheckDuplicateName();
}

void StateCreateWorld::OnResize(sf::Vector2u _size)
{
	sf::Vector2u winSize = Settings::GetWindowSize();
	float scale = Utils::Scale(1.f);

	background.OnResize(_size);

	spriteMenuBackground.setScale({ scale, scale });
	spriteMenuBackground.setPosition({ (float)_size.x / 2.f, (float)_size.y / 2.f });
	spriteCreatingWorld.setPosition({ _size.x / 2.f, _size.y / 2.f - Utils::Scale(250.f) });
	spriteCreatingWorld.setScale({ scale, scale });

	textCreatingWorld.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textCreatingWorld.SetPosition({ _size.x / 2.f - Utils::Scale(220.f), _size.y / 2.f - Utils::Scale(265.f) });
	textWorldName.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textWorldName.SetPosition({ _size.x / 2.f - Utils::Scale(270.f), _size.y / 2.f - Utils::Scale(180.f) });
	textWorldNameTip.SetCharacterSize((unsigned int)Utils::Scale(15.f));
	textWorldNameTip.SetPosition({ textWorldName.frontText.getGlobalBounds().left + textWorldName.frontText.getGlobalBounds().width + Utils::Scale(5.f), _size.y / 2.f - Utils::Scale(170.f) });
	textSeed.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textSeed.SetPosition({ _size.x / 2.f - Utils::Scale(270.f), _size.y / 2.f - Utils::Scale(70.f) });
	textSeedTip.SetCharacterSize((unsigned int)Utils::Scale(15.f));
	textSeedTip.SetPosition({ textSeed.frontText.getGlobalBounds().left + textSeed.frontText.getGlobalBounds().width + Utils::Scale(5.f), _size.y / 2.f - Utils::Scale(60.f)});
	textSize.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textSize.SetPosition({ _size.x / 2.f - Utils::Scale(270.f), _size.y / 2.f + Utils::Scale(35.f) });
	textBonusChest.SetCharacterSize((unsigned int)Utils::Scale(30.f));
	textBonusChest.SetPosition({ _size.x / 2.f - Utils::Scale(270.f), _size.y / 2.f + Utils::Scale(85.f) });

	inputWorldName.SetSize((unsigned int)(25.f * scale));
	inputWorldName.SetPosition({ _size.x / 2.f - Utils::Scale(260.f), _size.y / 2.f - Utils::Scale(125.f) });
	inputSeed.SetSize((unsigned int)(25.f * scale));
	inputSeed.SetPosition({ _size.x / 2.f - Utils::Scale(260.f), _size.y / 2.f - Utils::Scale(20.f) });
	optionSize.SetPosition({ _size.x / 2.f + Utils::Scale(125.f), _size.y / 2.f + Utils::Scale(40.f) });
	optionSize.SetSize((unsigned int)(25.f * scale));
	checkboxBonusChest.SetPosition({ _size.x / 2.f + Utils::Scale(190.f), _size.y / 2.f + Utils::Scale(105.f) });
	checkboxBonusChest.SetScale(scale * 0.15f);
	buttonCreate.SetSize((unsigned int)(25.f * scale));
	buttonCreate.SetPosition({ _size.x / 2.f - Utils::Scale(195.f), _size.y / 2.f + Utils::Scale(160.f) });
	buttonCancel.SetSize((unsigned int)(25.f * scale));
	buttonCancel.SetPosition({ _size.x / 2.f + Utils::Scale(195.f), _size.y / 2.f + Utils::Scale(160.f) });
}

void StateCreateWorld::OnEvent(sf::Event _event)
{
	if (_event.type == sf::Event::TextEntered)
	{
		inputWorldName.OnTextEntered(_event.text);
		inputSeed.OnTextEntered(_event.text);
		CheckDuplicateName();
	}
}

void StateCreateWorld::OnKeyPressed(sf::Event::KeyEvent _key)
{
	if (_key.code == sf::Keyboard::Escape)
	{
		Game::Get().SetState<StateSelectWorld>();
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
	}
}

void StateCreateWorld::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	inputWorldName.OnMousePressed(_mouse);
	inputSeed.OnMousePressed(_mouse);
	if (optionSize.OnMousePressed(_mouse))
	{
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}

	if (checkboxBonusChest.IsHovered())
	{
		checkboxBonusChest.Toggle();
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonCreate.isHovered && !buttonCreate.isDisabled)
	{
		if (inputWorldName.text.empty())
			inputWorldName.text = Language::Get().Translate("createworld.name.default");

		CheckDuplicateName();

		if (!duplicateName)
		{
			Game::Get().SetState<StateLoading>(inputWorldName.text, atoi(inputSeed.text.c_str()), checkboxBonusChest.IsToggled(), (unsigned int)optionSize.selectedIndex);
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		}
	}
	else if (buttonCancel.isHovered)
	{
		Game::Get().SetState<StateSelectWorld>();
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
	}
}

void StateCreateWorld::Update(float _deltaTime)
{
	background.Update(_deltaTime);
	optionSize.Update(_deltaTime);
	checkboxBonusChest.Update(_deltaTime);
	buttonCreate.Update(_deltaTime);
	buttonCancel.Update(_deltaTime);
}

void StateCreateWorld::Draw(sf::RenderTexture& _texture)
{
	background.Draw(_texture);
	_texture.draw(spriteMenuBackground);
	_texture.draw(spriteCreatingWorld);
	
	textCreatingWorld.Draw(_texture);
	textWorldName.Draw(_texture);
	textWorldNameTip.Draw(_texture);
	textSeed.Draw(_texture);
	textSeedTip.Draw(_texture);
	textSize.Draw(_texture);
	textBonusChest.Draw(_texture);
	inputWorldName.Draw(_texture);
	inputSeed.Draw(_texture);
	optionSize.Draw(_texture);
	checkboxBonusChest.Draw(_texture);
	buttonCreate.Draw(_texture);
	buttonCancel.Draw(_texture);
}

void StateCreateWorld::CheckDuplicateName()
{
	duplicateName = false;
	for (std::filesystem::path path : std::filesystem::directory_iterator("Saves/Worlds"))
	{
		if (std::filesystem::exists(path / "Regions") && std::filesystem::exists(path / "settings.bin"))
		{
			std::string pathLower = path.filename().string();
			std::transform(pathLower.begin(), pathLower.end(), pathLower.begin(),
				[](unsigned char c) { return std::tolower(c); });

			std::string defaultName = Language::Get().Translate("createworld.name.default");
			std::string inputLower = inputWorldName.text.empty() ? defaultName : inputWorldName.text;
			std::transform(inputLower.begin(), inputLower.end(), inputLower.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (pathLower == inputLower)
				duplicateName = true;
		}
	}

	inputWorldName.SetFocusColor(duplicateName ? sf::Color::Red : sf::Color::White);
	buttonCreate.isDisabled = duplicateName;
}
