#ifndef STELLAR_IMAGE_BUTTON_H
#define STELLAR_IMAGE_BUTTON_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class ImageButton
	{
	public:
		static ImageButton Create(const std::filesystem::path& _texturePath, sf::Vector2f _pos, float _scale = 1.f);

		void Update(float _deltaTime);
		void Draw(sf::RenderTexture& _rt);

		inline void SetPosition(sf::Vector2f _pos) { sprite.setPosition(_pos); }
		void SetScale(float _scale);

	public:
		sf::Sprite sprite;
		bool isHovered = false;
		bool isDisabled = false;
		float scale = 1.f;

	private:
		bool lastHovered = false;
	};

}

#endif