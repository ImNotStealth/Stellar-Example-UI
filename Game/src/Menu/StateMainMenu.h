#ifndef STATE_MAIN_MENU_H
#define STATE_MAIN_MENU_H

#include <Stellar/Stellar.h>

class StateMainMenu : public Stellar::GameState
{
public:
	StateMainMenu()
		: GameState("Main Menu") {}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void OnMousePressed(sf::Event::MouseButtonEvent _mouse) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;
public:
	static bool firstOpen;

private:
	sf::RectangleShape shapeFadeIn;
	Stellar::Easing easeFadeIn;
	
	sf::Sprite spriteLogo;
	Stellar::Button buttonPlay;
	Stellar::Button buttonSettings;
	Stellar::Button buttonQuit;
	Stellar::Text textExample;
	Stellar::Paragraph paragraphExample;
	Stellar::Checkbox checkbox;
	Stellar::ImageButton imageButton;
};

#endif