#include "Game.h"

#include "Stellar/Core/Settings.h"
#include "Stellar/Core/Language.h"
#include "Stellar/Core/AssetManager.h"
#include "Stellar/Debug/DebugOverlay.h"
#include "Stellar/Utils/SoundHandler.h"
#include "Stellar/Utils/MusicHandler.h"
#include <chrono>

namespace Stellar {

	Game& Game::Get()
	{
		if (!instance)
			instance = new Game();

		return *instance;
	}

	void Game::Set(Game* _instance)
	{
		if (instance)
			delete instance;

		instance = std::move(_instance);
	}

	void Game::SetSettings(WindowSettings _info)
	{
		windowSettings = _info;

#ifdef  STELLAR_DEBUG
		windowSettings.name += " (Debug)";
#endif

		Settings::Get().fpsLimit = _info.fpsLimit;
		Settings::Get().isFullscreen = _info.fullscreen;
		Settings::Get().isVSync = _info.vsync;
		Settings::Get().winSize = _info.winSize;
	}

	void Game::ToggleFullscreen(bool _fullscreen)
	{
		windowSettings.fullscreen = _fullscreen;
		Settings::Get().isFullscreen = _fullscreen;
		CreateWindow(windowSettings);

		if (currentState)
		{
			currentState->OnResize(Settings::GetWindowSize());
		}
	}

	void Game::CreateWindow(WindowSettings _info)
	{
		if (renderWindow.isOpen())
		{
			renderWindow.close();
		}
		
		sf::Vector2u windowSize = { _info.fullscreen ? sf::VideoMode::getDesktopMode().width : Settings::Get().winSize.x, _info.fullscreen ? sf::VideoMode::getDesktopMode().height : Settings::Get().winSize.y };
		sf::Uint32 noResizeStyle = sf::Style::Titlebar | sf::Style::Close;
		
		renderWindow.create(sf::VideoMode(windowSize.x, windowSize.y), windowSettings.name, _info.fullscreen ? sf::Style::None : _info.resizable ? sf::Style::Default : noResizeStyle);
		renderWindow.setFramerateLimit(_info.fpsLimit);
		renderWindow.setVerticalSyncEnabled(Settings::Get().isVSync);
		renderTexture.create(windowSize.x, windowSize.y);
		
		std::cout << "Created Window: " << "'" << windowSettings.name << "' (" << windowSize.x << "x" << windowSize.y << ", FPS: " << windowSettings.fpsLimit << ", Fullscreen: " << windowSettings.fullscreen << ", VSync: " << windowSettings.vsync << ")" << std::endl;

		sf::Image icon;
		std::string iconPath = "Assets/icon.png";
		if (std::filesystem::exists(iconPath) && icon.loadFromFile(iconPath))
		{
			renderWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		}
	}

	void Game::Run()
	{
		isRunning = true;
		Load();
		while (renderWindow.isOpen())
		{
			sf::Event event;
			while (renderWindow.pollEvent(event))
			{
				OnEvent(event);
			}

			Update();
			Draw();
		}
		Shutdown();
	}

	void Game::Load()
	{
		Settings::Get().LoadFromFile();
		Language::Get().SetLanguage(Settings::Get().language);

		windowSettings.fullscreen = Settings::Get().isFullscreen;
		windowSettings.vsync = Settings::Get().isVSync;
		windowSettings.fpsLimit = Settings::Get().fpsLimit;

		CreateWindow(windowSettings);

#ifdef STELLAR_DEBUG
		ImGui::SFML::Init(renderWindow);
		DebugOverlay::Get().Load();
#endif
		if (currentState)
		{
			currentState->Load();
			currentState->OnResize(Settings::GetWindowSize());
			std::cout << "Loaded GameState: " << currentState->GetDebugName() << std::endl;
		}
	}

	void Game::OnEvent(sf::Event _event)
	{
#ifdef STELLAR_DEBUG
		ImGui::SFML::ProcessEvent(renderWindow, _event);
#endif

		switch (_event.type)
		{
		case sf::Event::Closed:
			renderWindow.close();
			break;

		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(0, 0, (float)_event.size.width, (float)_event.size.height);
			renderWindow.setView(sf::View(visibleArea));
			renderTexture.create(_event.size.width, _event.size.height);
			Settings::Get().winSize = { _event.size.width, _event.size.height };

			// Reload the GameState to re-position their sprites etc
			if (currentState)
			{
				currentState->OnResize(Settings::GetWindowSize());
			}
			break;
		}
		case sf::Event::KeyPressed:
			OnKeyPressed(_event.key);
			break;
		case sf::Event::MouseButtonPressed:
			if (renderWindow.hasFocus())
			{
				if (currentState)
				{
					currentState->OnMousePressed(_event.mouseButton);
				}
			}
			break;
		case sf::Event::JoystickButtonPressed:
			if (currentState && renderWindow.hasFocus())
			{
				currentState->OnJoyPressed(_event.joystickButton);
			}
			break;
		case sf::Event::JoystickMoved:
			if (currentState && renderWindow.hasFocus())
			{
				currentState->OnJoyMoved(_event.joystickMove);
			}
			break;
		}

		if (currentState)
		{
			currentState->OnEvent(_event);
		}
	}

	void Game::OnKeyPressed(sf::Event::KeyEvent _key)
	{
		if (renderWindow.hasFocus())
		{
#ifdef STELLAR_DEBUG
			if (_key.code == sf::Keyboard::F1)
			{
				DebugOverlay::Get().ToggleDebug();
			}
#endif
			if (_key.code == sf::Keyboard::F11)
			{
				Game::Get().ToggleFullscreen(!Settings::Get().isFullscreen);
			}

			if (currentState)
			{
				currentState->OnKeyPressed(_key);
			}
		}
	}

	void Game::Update()
	{
		sf::Time time = clock.restart();
		float deltaTime = time.asSeconds();

#ifdef STELLAR_DEBUG
		ImGui::SFML::Update(renderWindow, time);
#endif

		if (currentState)
		{
			currentState->Update(deltaTime);
		}
#ifdef STELLAR_DEBUG
		DebugOverlay::Get().UpdateImGui(currentState, deltaTime);
#endif
		SoundHandler::Get().Update(deltaTime);

		if (loadingFuture.valid())
		{
			loadingFutureStatus = loadingFuture.wait_for(std::chrono::milliseconds(0));
			if (loadingFutureStatus == std::future_status::ready)
			{
				std::cout << "Loaded Async GameState: " << loadingState->GetDebugName() << std::endl;
				currentState = loadingState;
				currentState->OnResize(Settings::GetWindowSize());
				loadingFuture = {};
			}
		}
	}

	void Game::Draw()
	{
		renderWindow.clear(sf::Color::Black);
		renderTexture.clear();
		renderTexture.display();
		if (currentState)
		{
			currentState->Draw(renderTexture);
		}
		renderWindow.draw(sf::Sprite(renderTexture.getTexture()));
#ifdef STELLAR_DEBUG
		ImGui::SFML::Render(renderWindow);
#endif
		renderWindow.display();
	}

	void Game::Shutdown()
	{
		std::cout << "Shutting down." << std::endl;
		
		if (loadingFuture.valid())
		{
			std::cout << "Waiting for Async GameState to finish..." << std::endl;
			loadingFuture = {};
		}
		
		SoundHandler::Shutdown();
		MusicHandler::Shutdown();
		AssetManager::Shutdown();
		Settings::Shutdown();
#ifdef STELLAR_DEBUG
		DebugOverlay::Shutdown();
		ImGui::SFML::Shutdown();
#endif
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
}