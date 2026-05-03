#include "Animation.h"

namespace Stellar {

	Animation::Animation(sf::Sprite* _sprite, unsigned int _frameCount, float _frameRate, sf::IntRect _firstFrame, bool _isLooping, bool _isInteruptable, bool _isCentered)
		: sprite(_sprite), frameCount(_frameCount), frameRate(_frameRate), firstFrame(_firstFrame),
		isLooping(_isLooping), isInteruptable(_isInteruptable), isCentered(_isCentered)
	{
		shape = nullptr;
		currentFrame = 0;
		isFinished = false;
		timer = 0.f;
		isSprite = true;
		originBackup = sprite->getOrigin();
	}

	Animation::Animation(sf::Shape* _shape, unsigned int _frameCount, float _frameRate, sf::IntRect _firstFrame, bool _isLooping, bool _isInteruptable, bool _isCentered)
		: shape(_shape), frameCount(_frameCount), frameRate(_frameRate), firstFrame(_firstFrame),
		isLooping(_isLooping), isInteruptable(_isInteruptable), isCentered(_isCentered)
	{
		sprite = nullptr;
		currentFrame = 0;
		isFinished = false;
		timer = 0.f;
		isSprite = false;
		originBackup = shape->getOrigin();
	}

	void Animation::SetAnimation(Animation& _animation, Animation& _newAnimation)
	{
		if (&_animation != &_newAnimation)
		{
			if (_newAnimation.isFinished && !_newAnimation.isLooping)
			{
				_newAnimation.currentFrame = 0;
				_newAnimation.timer = 0.f;
			}

			// If the old animation is centered then we reset the sprite's origin to the new animation's origin.
			if (_animation.isCentered)
			{
				if (_animation.sprite)
				{
					_animation.sprite->setOrigin(_newAnimation.originBackup);
				}
				else
				{
					_animation.shape->setOrigin(_newAnimation.originBackup);
				}
			}

			_animation = _newAnimation;
		}
	}

	void Animation::AddFrameAction(int _frame, std::function<void()> _action)
	{
		FrameAction newAction;
		newAction.frame = _frame;
		newAction.action = _action;
		frameActions.push_back(newAction);
	}

	void Animation::UpdateActions()
	{
		for (const auto& action : frameActions)
		{
			if (action.frame == currentFrame && action.action)
			{
				action.action();
			}
		}
	}

	void Animation::Update(float _deltaTime)
	{
		timer += _deltaTime;
		if (timer > 1.f / frameRate)
		{
			// Next Frame
			if (!isFinished || isLooping)
			{
				currentFrame++;
				currentFrame %= frameCount;
				timer -= 1.f / frameRate;
				UpdateActions();
			}
			isFinished = currentFrame + 1 >= frameCount;
		}

		sf::IntRect actualFrame = firstFrame;
		actualFrame.left = firstFrame.left + currentFrame * firstFrame.width;

		if (isSprite)
		{
			sprite->setTextureRect(actualFrame);
			if (isCentered)
			{
				sf::Vector2f origin = sprite->getOrigin();
				sprite->setOrigin({ firstFrame.width / 2.f, origin.y });
			}
		}
		else
		{
			shape->setTextureRect(actualFrame);
			if (isCentered)
			{
				sf::Vector2f origin = shape->getOrigin();
				shape->setOrigin({ firstFrame.width / 2.f, origin.y });
			}
		}
	}

	void Animation::Draw(sf::RenderWindow& _window)
	{
		if (isSprite)
		{
			_window.draw(*sprite);
		}
		else
		{
			_window.draw(*shape);
		}
	}
}