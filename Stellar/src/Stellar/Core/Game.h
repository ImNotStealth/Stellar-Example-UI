#ifndef STELLAR_GAME_H
#define STELLAR_GAME_H

#include "Stellar/Core/Common.h"
#include "Stellar/Core/GameState.h"
#include "Stellar/Core/Settings.h"

namespace Stellar {

	struct WindowSettings
	{
		std::string name = "Stellar Engine";
		sf::Vector2u winSize = { 1280, 720 };
		unsigned int fpsLimit = 60;
		bool vsync = false;
		bool fullscreen = false;
		bool resizable = true;
	};

	class Game
	{
	public:
		// Sets the default settings used for when creating the game window (which is created when Run() is called).
		void SetSettings(WindowSettings _info);

		// Used to enable / disable fullscreen, also applies to Settings
		void ToggleFullscreen(bool _fullscreen);

		// Used to change any other window settings (FPS, Size etc.)
		void CreateWindow(WindowSettings _info);

		// Switches between GameStates, loading and cleaning up is done automatically.
		// It's a good idea to use 'return' after using this as the rest of your state code will be in an invalid state as it has now been destroyed.
		template <typename T, typename... Args>
		void SetState(Args&&... _args)
		{
			loadingState = nullptr;
			currentState = std::make_shared<T>(std::forward<Args>(_args)...);
			if (isRunning)
			{
				std::cout << "Loaded GameState: " << currentState->GetDebugName() << std::endl;
				currentState->Load();
				currentState->OnResize(Settings::GetWindowSize());
			}
		}

		// Switches between GameStates, loading and cleaning up is done automatically.
		template <typename T, typename... Args>
		void SetStateAsync(Args&&... _args)
		{
			loadingFuture = std::async(std::launch::async, [&]
			{
				loadingState = std::make_shared<T>(std::forward<Args>(_args)...);
				std::cout << "Loading GameState Async: " << loadingState->GetDebugName() << std::endl;
				loadingState->Load();
			});
		}

		// Gets the current GameState and casts it to T (can return nullptr if the cast failed)
		template<typename T>
		std::shared_ptr<T> GetState()
		{
			std::shared_ptr<T> state = std::dynamic_pointer_cast<T>(currentState);
			return state ? state : nullptr;
		}

		// Compares T to the current state
		template<typename T>
		bool IsState()
		{
			return typeid(T) == typeid(*currentState);
		}

		/*
			The main function to start the game.
			Only call once.
		*/
		void Run();

		// Get the instance of Game.
		static Game& Get();
		static void Set(Game* _instance);

		// Get the instance of RenderWindow. Can be used to modify window settings.
		inline sf::RenderWindow& GetRenderWindow() { return renderWindow; }
	
		inline sf::Clock GetClock() { return clock; }
	protected:
		virtual void Load();
		virtual void OnEvent(sf::Event _event);
		virtual void OnKeyPressed(sf::Event::KeyEvent _key);
		virtual void Update();
		virtual void Draw();
		virtual void Shutdown();

	protected:
		sf::RenderWindow renderWindow;
		sf::RenderTexture renderTexture;
		sf::Clock clock;
		WindowSettings windowSettings;
		bool isRunning;
		std::shared_ptr<GameState> currentState = nullptr;
		std::shared_ptr<GameState> loadingState = nullptr;
		std::future<void> loadingFuture;
		std::future_status loadingFutureStatus;
		inline static Game* instance;

		friend class StateEditor;
		friend class DebugBox2DRenderer;
	};
}

#endif