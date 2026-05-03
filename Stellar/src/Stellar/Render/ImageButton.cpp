#include "ImageButton.h"
#include "Stellar/Core/Game.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Utils/Utils.h"

namespace Stellar {

	ImageButton ImageButton::Create(const std::filesystem::path& _texturePath, sf::Vector2f _pos, float _scale)
	{
		ImageButton button;
		button.sprite.setTexture(AssetManager::GetTexture(_texturePath));

		button.SetScale(_scale);

		button.sprite.setPosition(_pos);
		return button;
	}

	void ImageButton::Update(float _deltaTime)
	{
		sf::FloatRect buttonBounds = sprite.getGlobalBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(Game::Get().GetRenderWindow());
		sf::Vector2f scaledMousePos = Game::Get().GetRenderWindow().mapPixelToCoords(mousePos);
		isHovered = buttonBounds.contains(scaledMousePos.x, scaledMousePos.y);

		if (isHovered != lastHovered)
		{
			Utils::SetCursor(isDisabled && isHovered ? sf::Cursor::Type::NotAllowed : isHovered ? sf::Cursor::Type::Hand : sf::Cursor::Type::Arrow);
		}

		lastHovered = isHovered;
	}

	void ImageButton::Draw(sf::RenderTexture& _rt)
	{
		_rt.draw(sprite);
	}

	void ImageButton::SetScale(float _scale)
	{
		scale = _scale;
		sprite.setScale({ scale, scale });

		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin({ bounds.width / 2.f, bounds.height / 2.f });
	}
}