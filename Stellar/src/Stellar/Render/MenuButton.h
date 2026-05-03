#ifndef STELLAR_MENU_BUTTON_H
#define STELLAR_MENU_BUTTON_H

#include "Stellar/Core/Common.h"
#include "Stellar/Render/Text.h"
#include "Stellar/Utils/Easing.h"

namespace Stellar
{
	class MenuButton
	{
	public:
		static MenuButton Create(const std::filesystem::path& _fontPath, const std::string& _langKey, sf::Vector2f _pos, unsigned int _fontSize = 30);
		static MenuButton Create(const std::filesystem::path& _fontPath, const std::filesystem::path& _spritePath, const std::string& _langKey, sf::Vector2f _pos, unsigned int _fontSize = 30);

		void Update(float _deltaTime);
		void Draw(sf::RenderTexture& _rt);

		void SetPosition(sf::Vector2f _pos);
		void SetSize(unsigned int _fontSize);

	public:
		Text label;
		sf::Sprite spriteBG;
		Easing easing;
		bool isHovered = false;
		bool isDisabled = false;

	private:
		sf::Vector2f pos;
		bool lastHovered = false;
		bool updateEasing = false;
		float scale = 1.f;
	};
}

#endif