#ifndef STATE_LOADING_H
#define STATE_LOADING_H

#include <Stellar/Stellar.h>
#include <Stellar/Utils/Easing.h>
#include "MenuBackground.h"

class StateLoading : public Stellar::GameState
{
public:
	StateLoading(std::string _name, int _seed = 0, bool _spawnChest = false, unsigned int _mapSize = 1)
		: GameState("Loading Screen"), worldName(_name), worldSeed(_seed), spawnChest(_spawnChest), mapSize(_mapSize) {}

	~StateLoading()
	{
		textStatus.reset();
		textStatus = nullptr;

		throbbers.clear();
	}

	void Load() override;
	void OnResize(sf::Vector2u _size) override;
	void Update(float _deltaTime) override;
	void Draw(sf::RenderTexture& _texture) override;

	void SetLoadState(std::string _msg);

private:
	MenuBackground background;
	std::unique_ptr<sf::Text> textStatus = nullptr; // <--- Fuck him, pain in my ass, crashes for no reason
	sf::Vector2f textStatusPos;

	float statusTime = 0.f;

	struct LoadingThrobber
	{
		sf::Sprite sprite;
		sf::Vector2f pos;
		Stellar::Easing easing;	
	};

	std::vector<std::shared_ptr<LoadingThrobber>> throbbers;
	bool resetting = false;
	unsigned int resettingIndex = 0;

	std::string worldName;
	int worldSeed;
	bool spawnChest;
	int mapSize;
};

#endif