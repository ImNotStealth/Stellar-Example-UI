#ifndef STELLAR_GAME_STATE_SPLASH_H
#define STELLAR_GAME_STATE_SPLASH_H

#include "Stellar/Core/GameState.h"
#include "Stellar/Utils/Easing.h"

namespace Stellar {

    template <typename T>
    class GameSplash : public GameState
    {
    public:
        GameSplash();

        void Load() override;
        void OnResize(sf::Vector2u _size) override;
        void OnEvent(sf::Event _event) override;
        void Update(float _deltaTime) override;
        void Draw(sf::RenderTexture& _texture) override;

    private:
        void NextSplash();
        void ScaleSprite(sf::Sprite& _sprite, sf::Vector2u& _textureSize, sf::Vector2u& _windowSize);

    private:
        int splashCount;
        Easing easingFadeIn;
        Easing easingFadeOut;
        std::vector<sf::Sprite> sprites;
    };

}

#include "GameSplash.cpp" // This is ugly I know

#endif