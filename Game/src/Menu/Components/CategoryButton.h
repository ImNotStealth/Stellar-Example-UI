#ifndef CATEGORY_BUTTON_H
#define CATEGORY_BUTTON_H

#include <Stellar/Core/Common.h>
#include <Stellar/Render/ImageButton.h>
#include <Stellar/Render/Text.h>
#include <Stellar/Utils/Easing.h>

class CategoryButton
{
public:
	static CategoryButton Create(const std::filesystem::path& _fontPath, const std::filesystem::path& _texturePath, std::string _labelKey, sf::Vector2f _pos, float _scale = 1.f);

	void Update(float _deltaTime);
	void Draw(sf::RenderTexture& _rt);

	void SetPosition(sf::Vector2f _pos);
	void SetScale(float _scale);

public:
	sf::Sprite spriteBG;
	sf::Sprite spriteIcon;
	Stellar::Text text;
	bool isHovered = false;
	bool isDisabled = false;
	float scale = 1.f;

private:
	Stellar::Easing easing;
	sf::Vector2f pos;
	bool lastHovered = false;
	bool updateEasing = false;
};

#endif