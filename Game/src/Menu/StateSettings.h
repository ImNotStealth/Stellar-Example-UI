#ifndef STATE_SETTINGS_H
#define STATE_SETTINGS_H

#include <Stellar/Stellar.h>
#include "Components/CategoryButton.h"
#include "Components/OptionButton.h"

class StateSettings : public Stellar::GameState
{
public:
	StateSettings()
		: GameState("Settings") {}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void OnEvent(sf::Event _event) override;
	void OnKeyPressed(sf::Event::KeyEvent _key) override;
	void OnMousePressed(sf::Event::MouseButtonEvent _mouse) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

private:
	unsigned int UIScaleToIndex(float _scale);
	float IndexToUIScale(unsigned int _index);

private:
	enum class SettingsCategory
	{
		GENERAL,
		DISPLAY,
		AUDIO
	};

	sf::Sprite spriteBackground;

	Stellar::Text textTitle;
	CategoryButton buttonCatGeneral;
	CategoryButton buttonCatDisplay;
	CategoryButton buttonCatAudio;
	Stellar::MenuButton buttonCredits;
	Stellar::MenuButton buttonBack;
	sf::RectangleShape shapeCatSeparator;

	Stellar::Text textLanguage;
	Stellar::Text textSimulationDistance;
	Stellar::Text textZoom;
	Stellar::Text textUIScale;
	Stellar::Text textTutorial;
	Stellar::Text textFullscreen;
	Stellar::Text textFps;
	Stellar::Text textVSync;
	Stellar::Text textVolumeMaster;
	Stellar::Text textVolumeMusic;
	Stellar::Text textVolumeSFX;
	Stellar::Text textVolumeUI;

	OptionButton optionLang;
	Stellar::Slider sliderSimulationDistance;
	Stellar::Slider sliderZoom;
	OptionButton optionUIScale;
	Stellar::Checkbox checkboxTutorial;
	Stellar::Checkbox checkboxFullscreen;
	OptionButton optionFps;
	Stellar::Checkbox checkboxVSync;

	Stellar::Slider sliderVolumeMaster;
	Stellar::Slider sliderVolumeMusic;
	Stellar::Slider sliderVolumeUI;
	Stellar::Slider sliderVolumeSFX;

	SettingsCategory selectedCategory = SettingsCategory::GENERAL;
};

#endif