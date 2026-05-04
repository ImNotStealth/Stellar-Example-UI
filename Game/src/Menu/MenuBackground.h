#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include <Stellar/Stellar.h>

class MenuBackground
{
public:
	void Load();
	void OnResize(sf::Vector2u _size);
	void Update(float _dt);
	void Draw(sf::RenderTexture& _rt);
	
private:
	void DrawBackground(sf::RenderTexture& _rt, std::vector<sf::Sprite>& _sprites);
	void SetBackground(unsigned int _index);
	unsigned int RandomIndex();

private:
	struct Background
	{
		std::string name;
		unsigned int chance; // The chance for the background to appear /100
	};

	static float xOffset;
	static float timer;
	static int backgroundIndex;
	std::vector<Background> backgroundPaths;
	std::vector<sf::Sprite> bg; // Main background
	std::vector<sf::Sprite> bgTrans; // The background used for fading
	Stellar::Easing easing;
};

#endif