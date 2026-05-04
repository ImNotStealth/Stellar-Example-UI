#include "StateSettings.h"

#include "StateMainMenu.h"
#include "StateCredits.h"
#include "Common.h"
#include "Menu/Components/CategoryButton.h"
#include "Menu/Components/OptionButton.h"
#include <Stellar/Utils/Utils.h>

using namespace Stellar;

void StateSettings::Load()
{
	spriteBackground.setTexture(AssetManager::GetTexture("UI/Background.png"));

	textTitle = Text::CreateCentered(UI_FONT_MAIN, Language::Get().Translate("settings.title"), {});

	buttonCatGeneral = CategoryButton::Create(UI_FONT_MAIN, "UI/Settings/General.png", "settings.general", {});
	buttonCatDisplay = CategoryButton::Create(UI_FONT_MAIN, "UI/Settings/Display.png", "settings.display", {});
	buttonCatAudio = CategoryButton::Create(UI_FONT_MAIN, "UI/Settings/Audio.png", "settings.audio", {});
	buttonCredits = MenuButton::Create(UI_FONT_TEXT, "mainmenu.credits", {});
	buttonBack = MenuButton::Create(UI_FONT_TEXT, "menu.back", {});

	textLanguage = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.language"), {});
	textSimulationDistance = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.simulationdistance"), {});
	textZoom = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.zoom"), {});
	textUIScale = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.uiscale"), {});
	textTutorial = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.tutorialhints"), {});
	textFullscreen = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.fullscreen"), {});
	textFps = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.fps"), {});
	textVSync = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.vsync"), {});
	textVolumeMaster = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.volume.master"), {});
	textVolumeMusic = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.volume.music"), {});
	textVolumeSFX = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.volume.sfx"), {});
	textVolumeUI = Text::Create(UI_FONT_TEXT, Language::Get().Translate("settings.volume.ui"), {});

	optionLang = OptionButton::Create(UI_FONT_TEXT, { "en_US", "fr_FR" }, Settings::Get().language, {});
	sliderSimulationDistance = Slider::Create(UI_FONT_TEXT, {}, Settings::Get().simulationDistance, 1.5f, 5.f, 0.5f, true);
	sliderZoom = Slider::Create(UI_FONT_TEXT, {}, Settings::Get().cameraZoom, 0.5f, 1.5f, 0.1f, true);
	optionUIScale = OptionButton::Create(UI_FONT_TEXT, { "settings.uiscale.small", "settings.uiscale.normal" , "settings.uiscale.large" }, UIScaleToIndex(Settings::Get().uiScale), {});
	checkboxTutorial = Checkbox::Create(CHECKBOX_TEXTURE, {}, 1.f, Settings::Get().showTutorialHints);

	checkboxFullscreen = Checkbox::Create(CHECKBOX_TEXTURE, {}, 1.f, Settings::Get().isFullscreen);
	std::vector<std::string> fpsOptions = { "settings.unlimited", "30", "60", "120", "144", "165", "240", "360" };
	auto it = std::find(fpsOptions.begin(), fpsOptions.end(), std::to_string(Settings::Get().fpsLimit));
	unsigned int fpsIndex = 1;
	if (it != fpsOptions.end())
		fpsIndex = (unsigned int)std::distance(fpsOptions.begin(), it);
	if (Settings::Get().fpsLimit == 0)
		fpsIndex = 0;
	optionFps = OptionButton::Create(UI_FONT_TEXT, fpsOptions, fpsIndex, {});
	checkboxVSync = Checkbox::Create(CHECKBOX_TEXTURE, {}, 1.f, Settings::Get().isVSync);

	sliderVolumeMaster = Slider::Create(UI_FONT_TEXT, {}, (float)Settings::Get().volumeMaster, 0.f, 100.f, 1.f, false);
	sliderVolumeMusic = Slider::Create(UI_FONT_TEXT, {}, (float)Settings::Get().volumeMusic, 0.f, 100.f, 1.f, false);
	sliderVolumeUI = Slider::Create(UI_FONT_TEXT, {}, (float)Settings::Get().volumeUI, 0.f, 100.f, 1.f, false);
	sliderVolumeSFX = Slider::Create(UI_FONT_TEXT, {}, (float)Settings::Get().volumeSFX, 0.f, 100.f, 1.f, false);
}

void StateSettings::OnResize(sf::Vector2u _size)
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
	float catSpacing = 100.f;
	textTitle.SetCharacterSize((unsigned int)(60.f * scale));
	textTitle.SetPosition({ (float)_size.x / 2.f, Utils::Scale(70.f) });

	buttonCatGeneral.SetPosition({ 50.f * scale, 230.f * scale });
	buttonCatGeneral.SetScale(Utils::Scale(0.8f));
	buttonCatDisplay.SetPosition({ 50.f * scale, (230.f + catSpacing) * scale });
	buttonCatDisplay.SetScale(Utils::Scale(0.8f));
	buttonCatAudio.SetPosition({ 50.f * scale, (230.f + catSpacing * 2.f) * scale });
	buttonCatAudio.SetScale(Utils::Scale(0.8f));
	buttonCredits.SetPosition({ winSize.x - Utils::Scale(350.f), winSize.y - Utils::Scale(50.f) });
	buttonCredits.SetSize((unsigned int)(30.f * scale));
	buttonBack.SetPosition({ winSize.x - Utils::Scale(125.f), winSize.y - Utils::Scale(50.f) });
	buttonBack.SetSize((unsigned int)(30.f * scale));

	shapeCatSeparator.setSize({ 7.5f * scale, _size.y - 200.f * scale });
	shapeCatSeparator.setOrigin({ shapeCatSeparator.getSize().x / 2.f, 0.f });
	shapeCatSeparator.setPosition({ 450.f * scale, Utils::Scale(100.f + 70.f) });

	float horOffset = shapeCatSeparator.getPosition().x + Utils::Scale(125.f);
	textLanguage.SetPosition({ horOffset, 230.f * scale });
	textLanguage.SetCharacterSize((unsigned int)(30.f * scale));
	textSimulationDistance.SetPosition({ horOffset, (230.f + catSpacing) * scale });
	textSimulationDistance.SetCharacterSize((unsigned int)(30.f * scale));
	textZoom.SetPosition({ horOffset, (230.f + catSpacing * 2.f) * scale });
	textZoom.SetCharacterSize((unsigned int)(30.f * scale));
	textUIScale.SetPosition({ horOffset, (230.f + catSpacing * 3.f) * scale });
	textUIScale.SetCharacterSize((unsigned int)(30.f * scale));
	textTutorial.SetPosition({ horOffset, (230.f + catSpacing * 4.f) * scale });
	textTutorial.SetCharacterSize((unsigned int)(30.f * scale));
	textFullscreen.SetPosition({ horOffset, 230.f * scale });
	textFullscreen.SetCharacterSize((unsigned int)(30.f * scale));
	textFps.SetPosition({ horOffset, (230.f + catSpacing) * scale });
	textFps.SetCharacterSize((unsigned int)(30.f * scale));
	textVSync.SetPosition({ horOffset, (230.f + catSpacing * 2.f) * scale });
	textVSync.SetCharacterSize((unsigned int)(30.f * scale));
	textVolumeMaster.SetPosition({ horOffset, 230.f * scale });
	textVolumeMaster.SetCharacterSize((unsigned int)(30.f * scale));
	textVolumeMusic.SetPosition({ horOffset, (230.f + catSpacing) * scale });
	textVolumeMusic.SetCharacterSize((unsigned int)(30.f * scale));
	textVolumeSFX.SetPosition({ horOffset, (230.f + catSpacing * 2.f) * scale });
	textVolumeSFX.SetCharacterSize((unsigned int)(30.f * scale));
	textVolumeUI.SetPosition({ horOffset, (230.f + catSpacing * 3.f) * scale });
	textVolumeUI.SetCharacterSize((unsigned int)(30.f * scale));

	optionLang.SetPosition({ winSize.x - 300.f * scale, 230.f * scale });
	optionLang.SetSize((unsigned int)(30.f * scale));
	sliderSimulationDistance.SetPosition({ winSize.x - 500.f * scale, (245.f + catSpacing) * scale });
	sliderSimulationDistance.SetSize((unsigned int)(30.f * scale));
	sliderZoom.SetPosition({ winSize.x - 500.f * scale, (245.f + (catSpacing * 2.f)) * scale });
	sliderZoom.SetSize((unsigned int)(30.f * scale));
	optionUIScale.SetPosition({ winSize.x - 300.f * scale, (230.f + catSpacing * 3.f) * scale });
	optionUIScale.SetSize((unsigned int)(30.f * scale));
	checkboxTutorial.SetPosition({ winSize.x - 220.f * scale, (250.f + catSpacing * 4.f) * scale });
	checkboxTutorial.SetScale(scale * 0.25f);
	
	checkboxFullscreen.SetPosition({ winSize.x - 220.f * scale, 250.f * scale });
	checkboxFullscreen.SetScale(scale * 0.25f);
	optionFps.SetPosition({ winSize.x - 300.f * scale, (250.f + catSpacing) * scale });
	optionFps.SetSize((unsigned int)(30.f * scale));
	checkboxVSync.SetPosition({ winSize.x - 220.f * scale, (250.f + catSpacing * 2.f) * scale });
	checkboxVSync.SetScale(scale * 0.25f);

	sliderVolumeMaster.SetPosition({ winSize.x - 500.f * scale, 245.f * scale });
	sliderVolumeMaster.SetSize((unsigned int)(30.f * scale));
	sliderVolumeMusic.SetPosition({ winSize.x - 500.f * scale, (245.f + catSpacing) * scale });
	sliderVolumeMusic.SetSize((unsigned int)(30.f * scale));
	sliderVolumeUI.SetPosition({ winSize.x - 500.f * scale, (245.f + catSpacing * 2.f) * scale });
	sliderVolumeUI.SetSize((unsigned int)(30.f * scale));
	sliderVolumeSFX.SetPosition({ winSize.x - 500.f * scale, (245.f + catSpacing * 3.f) * scale });
	sliderVolumeSFX.SetSize((unsigned int)(30.f * scale));
}

void StateSettings::OnEvent(sf::Event _event)
{
	switch (_event.type)
	{
	case sf::Event::MouseMoved:
		switch (selectedCategory)
		{
		case SettingsCategory::GENERAL:
			if (sliderSimulationDistance.OnMouseMoved(_event.mouseMove))
				Settings::Get().simulationDistance = sliderSimulationDistance.GetValue();

			else if (sliderZoom.OnMouseMoved(_event.mouseMove))
				Settings::Get().cameraZoom = sliderZoom.GetValue();
			break;

		case SettingsCategory::AUDIO:
			if (sliderVolumeMaster.OnMouseMoved(_event.mouseMove))
			{
				Settings::Get().volumeMaster = (unsigned int)sliderVolumeMaster.GetValue();
				MusicHandler::Get().UpdateVolume();
			}
			else if (sliderVolumeMusic.OnMouseMoved(_event.mouseMove))
			{
				Settings::Get().volumeMusic = (unsigned int)sliderVolumeMusic.GetValue();
				MusicHandler::Get().UpdateVolume();
			}
			else if (sliderVolumeUI.OnMouseMoved(_event.mouseMove))
				Settings::Get().volumeUI = (unsigned int)sliderVolumeUI.GetValue();

			else if (sliderVolumeSFX.OnMouseMoved(_event.mouseMove))
				Settings::Get().volumeSFX = (unsigned int)sliderVolumeSFX.GetValue();

			break;

		default:
			break;
		}
		break;

	case sf::Event::MouseButtonReleased:
		switch (selectedCategory)
		{
		case SettingsCategory::GENERAL:
			sliderSimulationDistance.OnMouseReleased(_event.mouseButton);
			sliderZoom.OnMouseReleased(_event.mouseButton);
			break;

		case SettingsCategory::AUDIO:
			sliderVolumeMaster.OnMouseReleased(_event.mouseButton);
			sliderVolumeMusic.OnMouseReleased(_event.mouseButton);
			sliderVolumeUI.OnMouseReleased(_event.mouseButton);
			sliderVolumeSFX.OnMouseReleased(_event.mouseButton);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void StateSettings::OnKeyPressed(sf::Event::KeyEvent _key)
{
	if (_key.code == sf::Keyboard::Escape)
	{
		Game::Get().SetState<StateMainMenu>();
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
		return;
	}
}

void StateSettings::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
{
	if (buttonCatGeneral.isHovered)
	{
		selectedCategory = SettingsCategory::GENERAL;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonCatDisplay.isHovered)
	{
		selectedCategory = SettingsCategory::DISPLAY;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonCatAudio.isHovered)
	{
		selectedCategory = SettingsCategory::AUDIO;
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
	}
	else if (buttonCredits.isHovered)
	{
		Game::Get().SetState<StateCredits>();
		SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		return;
	}
	else if (buttonBack.isHovered)
	{
		Game::Get().SetState<StateMainMenu>();
		SoundHandler::Get().Play(SND_UI_CANCEL, SoundType::UI);
		return;
	}

	switch (selectedCategory)
	{
	case SettingsCategory::GENERAL:
		if (optionLang.OnMousePressed(_mouse))
		{
			Settings::Get().language = (LangType)optionLang.selectedIndex;
			Language::Get().SetLanguage(Settings::Get().language);
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
			//SoundHandler::Get().Play(SND_UI_MISC, SoundType::SND_TYPE_UI);
			Load();
			OnResize(Settings::GetWindowSize());
		}
		else if (sliderSimulationDistance.OnMousePressed(_mouse))
		{
			Settings::Get().simulationDistance = sliderSimulationDistance.GetValue();
		}
		else if (sliderZoom.OnMousePressed(_mouse))
		{
			Settings::Get().cameraZoom = sliderZoom.GetValue();
		}
		else if (optionUIScale.OnMousePressed(_mouse))
		{
			Settings::Get().uiScale = IndexToUIScale(optionUIScale.selectedIndex);
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
			Load();
			OnResize(Settings::GetWindowSize());
		}
		else if (checkboxTutorial.IsHovered())
		{
			checkboxTutorial.Toggle();
			Settings::Get().showTutorialHints = checkboxTutorial.IsToggled();
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		}
		break;

	case SettingsCategory::DISPLAY:
		if (checkboxFullscreen.IsHovered())
		{
			checkboxFullscreen.Toggle();
			Game::Get().ToggleFullscreen(checkboxFullscreen.IsToggled());
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		}
		else if (optionFps.OnMousePressed(_mouse))
		{
			Settings::Get().fpsLimit = optionFps.selectedIndex == 0 ? 0 : std::stoi(optionFps.GetOptions().at(optionFps.selectedIndex));
			Game::Get().GetRenderWindow().setFramerateLimit(Settings::Get().fpsLimit);
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		}
		else if (checkboxVSync.IsHovered())
		{
			checkboxVSync.Toggle();
			Game::Get().GetRenderWindow().setVerticalSyncEnabled(checkboxVSync.IsToggled());
			Settings::Get().isVSync = checkboxVSync.IsToggled();
			SoundHandler::Get().Play(SND_UI_CLICK, SoundType::UI);
		}
		break;

	case SettingsCategory::AUDIO:
		if (sliderVolumeMaster.OnMousePressed(_mouse))
			Settings::Get().volumeMaster = (unsigned int)sliderVolumeMaster.GetValue();
		
		else if (sliderVolumeMusic.OnMousePressed(_mouse))
			Settings::Get().volumeMusic = (unsigned int)sliderVolumeMusic.GetValue();
		
		else if (sliderVolumeUI.OnMousePressed(_mouse))
			Settings::Get().volumeUI = (unsigned int)sliderVolumeUI.GetValue();
		
		else if (sliderVolumeSFX.OnMousePressed(_mouse))
			Settings::Get().volumeSFX = (unsigned int)sliderVolumeSFX.GetValue();
		break;

	default:
		break;
	}
}

void StateSettings::Update(float _deltaTime)
{
	buttonCatGeneral.Update(_deltaTime);
	buttonCatDisplay.Update(_deltaTime);
	buttonCatAudio.Update(_deltaTime);

	buttonCredits.Update(_deltaTime);
	buttonBack.Update(_deltaTime);

	switch (selectedCategory)
	{
	case SettingsCategory::GENERAL:
		optionLang.Update(_deltaTime);
		sliderSimulationDistance.Update(_deltaTime);
		sliderZoom.Update(_deltaTime);
		optionUIScale.Update(_deltaTime);
		checkboxTutorial.Update(_deltaTime);
		break;

	case SettingsCategory::DISPLAY:
		checkboxFullscreen.Update(_deltaTime);
		optionFps.Update(_deltaTime);
		checkboxVSync.Update(_deltaTime);
		break;

	case SettingsCategory::AUDIO:
		sliderVolumeMaster.Update(_deltaTime);
		sliderVolumeMusic.Update(_deltaTime);
		sliderVolumeUI.Update(_deltaTime);
		sliderVolumeSFX.Update(_deltaTime);
		break;

	default:
		break;
	}
}


void StateSettings::Draw(sf::RenderTexture& _texture)
{
	_texture.draw(spriteBackground);
	textTitle.Draw(_texture);

	buttonCatGeneral.Draw(_texture);
	buttonCatDisplay.Draw(_texture);
	buttonCatAudio.Draw(_texture);

	_texture.draw(shapeCatSeparator);

	switch (selectedCategory)
	{
	case SettingsCategory::GENERAL:
		textLanguage.Draw(_texture);
		textSimulationDistance.Draw(_texture);
		textZoom.Draw(_texture);
		textUIScale.Draw(_texture);
		textTutorial.Draw(_texture);
		optionLang.Draw(_texture);
		sliderSimulationDistance.Draw(_texture);
		sliderZoom.Draw(_texture);
		optionUIScale.Draw(_texture);
		checkboxTutorial.Draw(_texture);
		break;

	case SettingsCategory::DISPLAY:
		textFullscreen.Draw(_texture);
		textFps.Draw(_texture);
		textVSync.Draw(_texture);
		checkboxFullscreen.Draw(_texture);
		optionFps.Draw(_texture);
		checkboxVSync.Draw(_texture);
		break;

	case SettingsCategory::AUDIO:
		textVolumeMaster.Draw(_texture);
		textVolumeMusic.Draw(_texture);
		textVolumeSFX.Draw(_texture);
		textVolumeUI.Draw(_texture);
		sliderVolumeMaster.Draw(_texture);
		sliderVolumeMusic.Draw(_texture);
		sliderVolumeUI.Draw(_texture);
		sliderVolumeSFX.Draw(_texture);
		break;

	default:
		break;
	}

	buttonCredits.Draw(_texture);
	buttonBack.Draw(_texture);
}

unsigned int StateSettings::UIScaleToIndex(float _scale)
{
	if (_scale == 0.75f)
		return 0;

	if (_scale == 1.f)
		return 1;

	if (_scale == 1.25f)
		return 2;

	return 1;
}

float StateSettings::IndexToUIScale(unsigned int _index)
{
	if (_index == 0)
		return 0.75f;

	if (_index == 1)
		return 1.f;

	if (_index == 2)
		return 1.25f;

	return 1.f;
}
