<div align="center">
    <img src="/x64/Debug/Game/Assets/Logo.png" alt="Stellar"/>
</div>

# Stellar
What I like to call a "SFML game framework" but most of my colleagues called it the "Stellar Engine" because it sounded cooler. 

# Games
This was the framework used in 3 of our school game projects, 2 of which are available for download if you're interested:
- Niva: 2D die-and-retry platformer: [Steam](https://store.steampowered.com/app/3258800/Niva/) or [Creajeux](https://www.creajeux.fr/projet/niva/)
  - *When we made this game, we hadn't learned C++ yet, so the first version of Stellar was actually written in C! It was more of a UI library back then though.*
<div align="center">
    <img src="/docs/imgs/Niva.png" width="75%" height="75%" alt="Niva"/>
</div>

- Hexatak: An online multiplayer isometrical tactical board game (sheesh that's a lot of adjectives...)
<div align="center">
    <img src="/docs/imgs/Hexatak.png" width="75%" height="75%" alt="Hexatak"/>
</div>

- Godbreak: Terraria-like 2D sandbox survival game: [Creajeux](https://www.creajeux.fr/projet/godbreak/)
<div align="center">
    <img src="/docs/imgs/Godbreak.png" width="75%" height="75%" alt="Godbreak"/>
</div>

*(Creajeux is the school I'm attending, they post our games there too!)*

# Content
So! Let's talk about what the framework actually has:
- GameStates
  - Switch between GameStates with at runtime (similar to switching scenes in Unity for example).
  - You can also load them async too! This can allow you to have a loading screen.
- ImGui Debug tools
  - Allows you to have global or GameState specific tools to debug your code.
- Controller support
  - Supports generic XInput controllers, PS4 and PS5 controllers.
- Game settings
  - Easily add game settings that can be read/written from anywhere in your code.
- Localization
  - Translate strings from a `.lang` file.
- SoundHandler
  - Play sounds and assign them a category so the user can adjust sound levels (Master, Music, UI etc.).
- Networking
  - Support for Host and Clients (no headless support, so no dedicated servers :/).
  - Easy to use packet system with read, write and handle functions.
- Editor
  - *Not included here as the scope of most games using this framework probably won't need this but I'm still listing it here to show what's possible.*
  - A seperate application from the game which can allow developers to create game specific assets. (*We used it to create the premade structures in Godbreak!*)
- Box2D
  - Included by default, also comes with a debug renderer so you can see collisions, velocities etc.
- A suite of UI Components (buttons, text, sliders, text inputs, checkboxes, etc.)
- Easings (implementation of [Easings](https://easings.net))
- Spritesheet Animations

# Getting started
You should be able to just clone this template, open the solution and hit compile.
Every asset in the `Debug/Assets` folder will be copied to `Release/Assets` if you're running in Release mode.

To start using the framework, you can look in the [docs](/docs) folder, I've provided a few samples on the important things to get you going!

# Things to improve
A few things can be improved I think, nothing that can stop you from making a game though.

The AssetManager here is more of a utility that loads assets in one liners.
While this is useful, nothing actually unloads any asset... ever... so once an asset has been loaded, it'll stay loaded until shutdown.
The games we made were also small enough that this never mattered but we started hitting the limits with Godbreak as we had multiple HD backgrounds and spritesheets at the same time.
I already have an idea on how to manage this but I'm torn on if I should leave the framework *as is* as a sort of code screenshot or try to make it the best I can.

GameStates have a small oversight which depending on how you use them could be quite annoying. You can only have one active at a time, it would've been better to use a stack of sorts where events propagate through them so you could have a debug layer, a UI layer, game layer etc.
Again the framework was made when only one GameState was ever needed so this was never required.

Settings are bit annoying to add and set, you have to add them in multiple areas and write multiple lines of code to set some settings. It'd be best to have functions to set the settings and call the necessarry code instead of having direct access to the variables.

Another thing I'd like to improve is to add a build system and to be honest I'm still learning CMake and I can't get it working without having to regenerate the solution everytime I add a file so I rather not use it for now.
Also I'm planning on sharing this with people at my school that may use this so I don't want to share something that isn't straightfoward or has unnecessary kinks.

*By the way, as of the time of writing this, this code is a little more than a year old so there may be mistakes/design flaws that I wouldn't make today.*
