#ifndef STATE_CREATE_WORLD_H
#define STATE_CREATE_WORLD_H

#include <Stellar/Stellar.h>
#include "MenuBackground.h"
#include "Components/OptionButton.h"

class StateCreateWorld : public Stellar::GameState
{
public:
	StateCreateWorld()
		: GameState("Create World") {}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void OnEvent(sf::Event _event) override;
	void OnKeyPressed(sf::Event::KeyEvent _key) override;
	void OnMousePressed(sf::Event::MouseButtonEvent _mouse) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

private:
	void CheckDuplicateName();

private:
	MenuBackground background;
	sf::Sprite spriteMenuBackground;
	sf::Sprite spriteCreatingWorld;
	Stellar::Text textCreatingWorld;
	Stellar::Text textWorldName;
	Stellar::Text textWorldNameTip;
	Stellar::Text textSeed;
	Stellar::Text textSeedTip;
	Stellar::Text textSize;
	Stellar::Text textBonusChest;
	Stellar::Textbox inputWorldName;
	Stellar::Textbox inputSeed;
	OptionButton optionSize;
	Stellar::Checkbox checkboxBonusChest;
	Stellar::MenuButton buttonCancel;
	Stellar::MenuButton buttonCreate;

	bool duplicateName = false;
};

#endif