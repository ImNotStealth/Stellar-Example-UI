#ifndef OPTION_BUTTON_H
#define OPTION_BUTTON_H

#include <Stellar/Core/Common.h>
#include <Stellar/Render/Text.h>
#include <Stellar/Render/Button.h>

class OptionButton
{
public:
	static OptionButton Create(const std::filesystem::path& _fontPath, std::vector<std::string> _options, unsigned int _defaultIndex, sf::Vector2f _pos, unsigned int _fontSize = 30);

	bool OnMousePressed(sf::Event::MouseButtonEvent _mouse);
	void Update(float _deltaTime);
	void Draw(sf::RenderTexture& _rt);
	void SetPosition(sf::Vector2f _pos);
	void SetSize(unsigned int _fontSize);

	inline const std::vector<std::string>& GetOptions() { return options; }

public:
	unsigned int selectedIndex = 0;
	bool isHovered = false;

private:
	Stellar::Text label;
	Stellar::Button buttonLeft;
	Stellar::Button buttonRight;
	sf::Vector2f pos;
	std::vector<std::string> options;
};

#endif