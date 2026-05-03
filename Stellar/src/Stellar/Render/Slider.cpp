#include "Slider.h"

#include "Stellar/Core/Game.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Utils/Utils.h"
#include <iomanip>

namespace Stellar
{
	Slider Slider::Create(const std::filesystem::path& _fontPath, sf::Vector2f _pos, float _value, float _minValue, float _maxValue, float _step, bool _useDecimals, unsigned int _fontSize)
	{
		Slider slider;
		slider.spriteBG.setTexture(AssetManager::GetTexture("UI/Settings/Slider_Background.png"));
		slider.spriteThumb = Utils::LoadSprite("UI/Settings/Slider_Thumb.png", true);
		slider.SetSize(_fontSize);
		slider.width = slider.spriteBG.getLocalBounds().width;
		slider.minValue = _minValue;
		slider.maxValue = _maxValue;
		slider.step = _step;
		slider.useDecimals = _useDecimals;
		slider.value = slider.NormalizeValue(_value);

		std::string label = std::to_string(_value);
		slider.textValue = Text::Create(_fontPath, label, _pos, _fontSize);
		return slider;
	}

	bool Slider::OnMousePressed(sf::Event::MouseButtonEvent _mouse)
	{
		if (!isHovered)
			return false;

		value = std::clamp<float>((_mouse.x - pos.x) / (width * (scale / 1.5f)), 0.f, 1.f);
		float f = DenormalizeValue(value);
		value = NormalizeValue(useDecimals ? f : round(f));
		isDragging = true;

		return true;
	}

	bool Slider::OnMouseMoved(sf::Event::MouseMoveEvent _mouse)
	{
		if (!isDragging)
			return false;
	
		value = std::clamp<float>((_mouse.x - pos.x) / (width * (scale / 1.5f)), 0.f, 1.f);
		float f = DenormalizeValue(value);
		value = NormalizeValue(useDecimals ? f : round(f));

		return true;
	}

	void Slider::OnMouseReleased(sf::Event::MouseButtonEvent _mouse)
	{
		isDragging = false;
	}

	void Slider::Update(float _deltaTime)
	{
		sf::FloatRect buttonBounds = spriteBG.getGlobalBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Get().GetRenderWindow());
		isHovered = buttonBounds.contains((float)mousePos.x, (float)mousePos.y);

		if (isHovered != lastHovered)
			Utils::SetCursor(isDisabled && isHovered ? sf::Cursor::Type::NotAllowed : isHovered ? sf::Cursor::Type::SizeHorizontal : sf::Cursor::Type::Arrow);

		//spriteThumb.setPosition({ pos.x + value * (width * scale), pos.y });
		spriteThumb.setPosition({ pos.x + value * (width * (scale / 1.5f)), pos.y + (spriteBG.getGlobalBounds().height / 2.f) });

		std::ostringstream stream;
		stream << std::fixed << std::setprecision(useDecimals) << DenormalizeValue(value);
		std::string displayString = stream.str();

		textValue.SetString(displayString);
		textValue.SetPosition({ pos.x - 85.f * scale, pos.y - 10.f * scale });

		lastHovered = isHovered;
	}

	void Slider::Draw(sf::RenderTexture& _rt)
	{
		_rt.draw(spriteBG);
		_rt.draw(spriteThumb);
		textValue.Draw(_rt);
	}

	void Slider::SetPosition(sf::Vector2f _pos)
	{
		pos = _pos;
		spriteBG.setPosition(_pos);
	}

	void Slider::SetSize(unsigned int _fontSize)
	{
		scale = (float)_fontSize / 30.f;

		spriteBG.setScale({ scale / 1.5f, scale / 1.5f });
		spriteThumb.setScale({ scale / 1.5f, scale / 1.5f });
		textValue.SetCharacterSize(_fontSize);
	}

	float Slider::NormalizeValue(float _value)
	{
		return std::clamp<float>((SnapToStepClamp(_value) - minValue) / (maxValue - minValue), 0.f, 1.f);
	}

	float Slider::DenormalizeValue(float _value)
	{
		return SnapToStepClamp(minValue + (maxValue - minValue) * std::clamp<float>(_value, 0.f, 1.f));
	}

	float Slider::SnapToStepClamp(float _value)
	{
		return std::clamp<float>(SnapToStep(_value), minValue, maxValue);
	}

	float Slider::SnapToStep(float _value)
	{
		if (step > 0.f)
			_value = step * round(_value / step);

		return _value;
	}
}
