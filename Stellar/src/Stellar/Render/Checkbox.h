#ifndef STELLAR_CHECKBOX_H
#define STELLAR_CHECKBOX_H

#include "Stellar/Core/Common.h"
#include "Stellar/Render/ImageButton.h"

namespace Stellar
{
	class Checkbox
	{
	public:
		static Checkbox Create(const std::filesystem::path& _texturePath, sf::Vector2f _pos, float _scale = 1.f, bool _isToggled = false);

		void Update(float _deltaTime);
		void Draw(sf::RenderTexture& _rt);
		void SetPosition(sf::Vector2f _pos);
		void SetScale(float _scale);

		void SetToggled(bool _toggled);
		inline void Toggle() { SetToggled(!IsToggled()); }
		inline bool IsToggled() { return isToggled; }
		inline bool IsHovered() { return button.isHovered; }

	public:
		ImageButton button;

	private:
		bool isToggled = false;
	};
}

#endif