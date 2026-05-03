#ifndef STELLAR_GAME_STATE_H
#define STELLAR_GAME_STATE_H

#include "Stellar/Core/Common.h"

namespace Stellar {

	class GameState
	{
	public:
		GameState(std::string _debugName)
			: debugName(_debugName) {}

		/*virtual ~GameState()
		{
			std::cout << "Destroyed GameState: " << debugName << std::endl;
		}*/

		virtual void Load() {}
		virtual void OnResize(sf::Vector2u _size) {}
		virtual void OnEvent(sf::Event _event) {}
		virtual void OnKeyPressed(sf::Event::KeyEvent _key) {}
		virtual void OnMousePressed(sf::Event::MouseButtonEvent _mouse) {}
		virtual void OnJoyPressed(sf::Event::JoystickButtonEvent _joy) {}
		virtual void OnJoyMoved(sf::Event::JoystickMoveEvent _joy) {}
		virtual void Update(float _deltaTime) {}
		virtual void UpdateImGui(float _deltaTime) {}
		virtual void Draw(sf::RenderTexture& _texture) {}

		// Used for debugging and printing the GameState's name in the console.
		inline std::string& GetDebugName() { return debugName; }

	private:
		std::string debugName;
	};

}

#endif