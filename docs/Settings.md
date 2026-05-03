# Settings
Useful for retrieving the window size, and the player's game settings.

# Samples
```c++
sf::Vector2u winSize = Stellar::Settings::GetWindowSize();
unsigned int fpsLimit = Stellar::Settings::Get().fpsLimit;
// Etc.
```
`GetWindowSize` returns the final size meaning if the game is in fullscreen, it'll return the display size, if it's in windowed mode, it'll return the user's window size.

To set the window to fullscreen, you can do so with one line. This will also be reflected in Settings so no need to set it there as well. You can also toggle it by pressing F11.
```c++
Game::Get().ToggleFullscreen(true);
```

To set the FPS limit, you'll need to set it in two places:
```c++
Settings::Get().fpsLimit = 60; // Apply it in settings for it to be loaded on restart.
Game::Get().GetRenderWindow().setFramerateLimit(Settings::Get().fpsLimit); // Apply it to the window
```

Similar to FPS, to set the VSync, you'll also need to do it in two places:
```c++
Settings::Get().isVSync = true;
Game::Get().GetRenderWindow().setVerticalSyncEnabled(Settings::Get().isVSync);
```

To set the game's language:
```c++
Settings::Get().language = LangType::FR_FR;
Language::Get().SetLanguage(Settings::Get().language);

// This reloads the current GameState
Load();
OnResize(Settings::GetWindowSize());
```

To set the UI scale:
```c++
// 0.75f for Small, 1.f for Normal and 1.25f for Large
// Nothing stops you from using other values in between though
Settings::Get().uiScale = 1.25f;

// This reloads the current GameState
Load();
OnResize(Settings::GetWindowSize());
```

By default, the framework has 4 volume sliders, Master (if none specified), Music, UI and SFX.\
To change the volume of any of these sliders, you can do so with:\
*`UpdateVolume` is only to update the sound of the current music track, the setting will be used for any future sound of music played.*
```c++
Settings::Get().volumeMaster = 60;
MusicHandler::Get().UpdateVolume();

Settings::Get().volumeMusic = 40;
MusicHandler::Get().UpdateVolume();

Settings::Get().volumeUI = 75;
Settings::Get().volumeSFX = 100;
```

To change the deadzone of your controllers, you can do so with:
```c++
Settings::Get().controllerDeadZone = 25.f;
// This option was added before multi-controller support was added so I didn't think to go back and add a deadzone setting for each controller.
```

# Adding a setting

If you want to add your own setting, you can do so by going in the Setting header and source files found [here](../Stellar/src/Stellar/Core/Settings.h) and [here](../Stellar/src/Stellar/Core/Settings.cpp) and adding the necessary code. If you look at how the other settings are listed, it should be fairly easy to add your own.

If you want to also add them to the Debug Overlay, you can find the file needed [here](../Stellar/src/Stellar/Debug/DebugOverlay.cpp).