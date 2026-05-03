#include "Checkbox.h"

namespace Stellar
{
	Checkbox Checkbox::Create(const std::filesystem::path& _texturePath, sf::Vector2f _pos, float _scale, bool _isToggled)
	{
		Checkbox checkboxFullscreen;
		checkboxFullscreen.button = ImageButton::Create(_texturePath, _pos, _scale);
		checkboxFullscreen.SetToggled(_isToggled);
		return checkboxFullscreen;
	}

	void Checkbox::Update(float _deltaTime)
	{
		button.Update(_deltaTime);
	}

	void Checkbox::Draw(sf::RenderTexture& _rt)
	{
		button.Draw(_rt);
	}

	void Checkbox::SetPosition(sf::Vector2f _pos)
	{
		button.SetPosition(_pos);
	}

	void Checkbox::SetToggled(bool _toggled)
	{
		isToggled = _toggled;
		sf::Vector2u bounds = button.sprite.getTexture()->getSize();
		button.sprite.setTextureRect({ isToggled ? (int)bounds.x / 2 : 0, 0, (int)bounds.x / 2, (int)bounds.y });
		button.sprite.setOrigin({ bounds.x / 4.f, bounds.y / 2.f });
	}


	void Checkbox::SetScale(float _scale)
	{
		button.SetScale(_scale);
	}
}