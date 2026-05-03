#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <Stellar/Stellar.h>

class StateTest : public Stellar::GameState
{
public:
	StateTest()
		: GameState("Test Menu") {}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void OnMousePressed(sf::Event::MouseButtonEvent _mouse) override;
	void Update(float _deltaTime) override;
	void UpdateImGui(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

private:
	Stellar::Button buttonBack;
};

#endif