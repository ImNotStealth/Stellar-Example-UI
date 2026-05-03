# Game

Neck a neck to GameState for the most important thing in the framework, this class handles the lifetime of your game and manages switching GameStates.

# Setup
To create a game, you'll need to specify a few things in your main function.\
We'll go over what you need in a few seconds.
```c++
#include <Stellar/Stellar.h>

#include "Menu/StateMainMenu.h"

using namespace Stellar;

int main()
{
    WindowSettings settings;
    settings.name = "Stellar Game";
    settings.winSize = { 1920, 1080 };
    settings.fpsLimit = 60;
    settings.vsync = true;
    settings.fullscreen = true;
    settings.resizable = false;
	Game::Get().SetSettings(settings);
	Game::Get().SetState<StateMainMenu>();
	Game::Get().Run();
	return 0;
}
```
`SetSettings` is used to specify the default window settings. With it, you can set the default window size, FPS, VSync, if the window is resizable, if the window should start in fullscreen and most importantly, the window's name :)\
If the user decides to change the FPS, VSync, size or fullscreen, the framework will use those settings instead.

`Run` is **only** called once and in the main function. This is what starts your game and shuts it down.\
Technically, it's the only function needed to actually start the framework, the rest is just for default settings.

# SetState
Once you've created your [GameState](GameState.md), you can use it with:
```c++
Stellar::Game::Get().SetState<StateSandbox>(Args); // 'Args' being your GameState's constructor parameters if you have any
```

> [!WARNING]
> Do note that setting the GameState destroys your current one, so if you are running code after having set your GameState, your game might crash as your previous GameState has now been destroyed.\
> To fix this, just add a `return` statement after having set your GameState.

Example:

```c++
if (button.isHovered)
{
    // Bad, bob will be destroyed and will cause a crash
    Stellar::Game::Get().SetState<StateSandbox>(Args);
}
bob.Update(_deltaTime);

//////////////

if (button.isHovered)
{
    // Good, the return statement stops bob from ever being updated and won't cause a crash
    Stellar::Game::Get().SetState<StateSandbox>(Args);
    return;
}
bob.Update(_deltaTime);

//////////////

bob.Update(_deltaTime);
if (button.isHovered)
{
    // Works, bob has been updated before you set your GameState and won't cause a crash
    // Don't bother coding in a way where SetState is always at the end of your code, just use returns instead
    Stellar::Game::Get().SetState<StateSandbox>(Args);
}
```

# SetStateAsync
Using `SetState` will block the main thread until it's done loading, `SetStateAsync` will instead spin up a new thread and load the new GameState and only switch to it once it's done loading. This was added near the end of when I worked on the framework so I haven't had time to really test it but it doesn't seem to have the same restrictions as `SetState` has with when/how to use it.
```c++
Stellar::Game::Get().SetStateAsync<StateSandbox>(Args); // 'Args' being your GameState's constructor parameters if you have any
```
You can use this to create a loading screen if you're loading a ton of assets or generating a world. We've actually done this with Godbreak and a sample can be found here. TODO: Add loading sample 

# GetState
If you need to retrieve your current GameState, you can do so with:
```c++
auto& state = Stellar::Game::Get().GetState<StateSandbox>();
```

# IsState
If you need to compare the current GameState with the one you provided:
```c++
bool isState = Stellar::Game::Get().IsState<StateMainMenu>();
// If the current GameState is StateSandbox, this will return false
```

# GetRenderWindow
Returns the sf::RenderWindow, useful if you need to grab the mouse position relative to the window
```c++
sf::RenderWindow& renderWindow = Stellar::Game::Get().GetRenderWindow();
```