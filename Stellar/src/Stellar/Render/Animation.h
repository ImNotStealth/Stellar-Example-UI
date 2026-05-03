#ifndef STELLAR_ANIMATION_H
#define STELLAR_ANIMATION_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class Animation
	{
	public:
		struct FrameAction
		{
			int frame;
			std::function<void()> action;
		};

		Animation() = default;
		Animation(sf::Sprite* _sprite, unsigned int _frameCount, float _frameRate, sf::IntRect _firstFrame, bool _isLooping = true, bool _isInteruptable = true, bool _isCentered = false);
		Animation(sf::Shape* _shape, unsigned int _frameCount, float _frameRate, sf::IntRect _firstFrame, bool _isLooping = true, bool _isInteruptable = true, bool _isCentered = false);

		void AddFrameAction(int _frame, std::function<void()> _action);
		void UpdateActions();
		void Update(float _deltaTime);
		void Draw(sf::RenderWindow& _window);

		static void SetAnimation(Animation& _animation, Animation& _newAnimation);

	public:
		sf::Sprite* sprite;
		sf::Shape* shape;
		unsigned int currentFrame;
		unsigned int frameCount;
		float frameRate;
		sf::IntRect firstFrame;
		bool isLooping;
		bool isInteruptable;
		bool isCentered;
		bool isFinished;
		float timer;

	private:
		
		std::vector<FrameAction> frameActions;
		bool isSprite;
		sf::Vector2f originBackup;
	};

}

#endif