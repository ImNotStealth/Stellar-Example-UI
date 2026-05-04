#ifndef STATE_CREDITS_H
#define STATE_CREDITS_H

#include <Stellar/Stellar.h>

class StateCredits : public Stellar::GameState
{
public:
	StateCredits()
		: GameState("Credits") {
	}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void OnKeyPressed(sf::Event::KeyEvent _key) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

private:
	sf::RectangleShape shapeFade;
	Stellar::Easing easeFade;

	sf::Sprite spriteBackground;

	sf::Sprite spriteLogo;
	std::vector<Stellar::Text> credits;

	float beginTimer = 0.f;
	float endTimer = 0.f;
	float totalOffset = 0.f;
	bool startedEndFade = false;
};

#endif