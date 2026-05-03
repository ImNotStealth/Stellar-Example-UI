#include "Utils.h"

#include "Stellar/Core/Game.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Core/Settings.h"

namespace Stellar {

	float Utils::Scale(float _value)
	{
		sf::Vector2u refSize = { 1920, 1080 };
		sf::Vector2u winSize = Game::Get().GetRenderWindow().getSize();
		return (_value * std::min((float)winSize.x / refSize.x, (float)winSize.y / refSize.y)) * Settings::Get().uiScale;
	}

	void Utils::SetCursor(sf::Cursor::Type _type)
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(_type);
		Game::Get().GetRenderWindow().setMouseCursor(cursor);
	}

	float Utils::IsFloatEqual(float _a, float _b, float _tolerance)
	{
		if (_a == _b)
		{
			return true;
		}

		double diff = fabs((double)(_a - _b));
		return diff <= _tolerance;
	}

	sf::Sprite Utils::LoadSprite(const std::filesystem::path& _path, bool _isCentered)
	{
		const sf::Texture& texture = AssetManager::GetTexture(_path);
		sf::Sprite tempSprite;
		tempSprite.setTexture(texture);

		if (_isCentered) 
		{
			sf::Vector2u size = texture.getSize();
			tempSprite.setOrigin({ size.x / 2.f, size.y / 2.f });
		}

		return tempSprite;
	}
}