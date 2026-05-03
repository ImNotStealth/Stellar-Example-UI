#ifndef STELLAR_SLIDER_H
#define STELLAR_SLIDER_H

#include "Stellar/Core/Common.h"
#include "Stellar/Render/Text.h"

namespace Stellar
{
	class Slider
	{
	public:
		static Slider Create(const std::filesystem::path& _fontPath, sf::Vector2f _pos, float _value, float _minValue, float _maxValue, float _step, bool _useDecimals, unsigned int _fontSize = 30);

		bool OnMousePressed(sf::Event::MouseButtonEvent _mouse);
		bool OnMouseMoved(sf::Event::MouseMoveEvent _mouse);
		void OnMouseReleased(sf::Event::MouseButtonEvent _mouse);
		void Update(float _deltaTime);
		void Draw(sf::RenderTexture& _rt);

		void SetPosition(sf::Vector2f _pos);
		void SetSize(unsigned int _fontSize);

		inline float GetValue() { return DenormalizeValue(value); }

	public:
		Text textValue;
		sf::Sprite spriteBG;
		sf::Sprite spriteThumb;
		bool isHovered = false;
		bool isDisabled = false;

	private:
		float NormalizeValue(float _value);
		float DenormalizeValue(float _value);
		float SnapToStepClamp(float _value);
		float SnapToStep(float _value);

	private:
		sf::Vector2f pos;
		bool lastHovered = false;
		bool isDragging = false;
		bool useDecimals = false;
		float scale = 1.f;
		float width = 100.f;
		float value = 0.f;
		float minValue = 0.f, maxValue = 10.f, step = 1.f;
	};
}

#endif