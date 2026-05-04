#ifndef STATE_SELECT_WORLD_H
#define STATE_SELECT_WORLD_H

#include <Stellar/Stellar.h>
#include "SaveEntry.h"
#include "MenuBackground.h"

class StateSelectWorld : public Stellar::GameState
{
public:
	StateSelectWorld()
		: GameState("Select World") {}

	void Load() override;
	void OnEvent(sf::Event _event) override;
	void OnResize(sf::Vector2u _size) override;
	void OnKeyPressed(sf::Event::KeyEvent _key) override;
	void OnMousePressed(sf::Event::MouseButtonEvent _mouse) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

private:
	void SetEntryPositions();

private:
	MenuBackground background;
	sf::Sprite spriteMenuBackground;
	Stellar::ImageButton buttonNewGame;
	Stellar::ImageButton buttonTutorial;
	Stellar::Text textNewGame;
	Stellar::Text textTutorial;
	Stellar::Text textNoWorlds;

	Stellar::ImageButton buttonUp;
	Stellar::ImageButton buttonDown;
	Stellar::MenuButton buttonBack;

	unsigned int saveIndexOffset = 0;
	std::vector<SaveEntry> saveEntries;
	std::vector<std::filesystem::path> worldPaths;
};

#endif