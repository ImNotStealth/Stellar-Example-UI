# AssetManager
A very useful piece of code that turns loading assets from a chore to a one liner!
It can load assets of type: `sf::Texture`, `sf::Font`, `sf::SoundBuffer` and `sf::Music`.\
If the asset hasn't been loaded before, it'll load it automatically.\
If it has been loaded, it'll retrieve it from memory which only makes loading the asset "slow" the first time!

# Sample
```c++
sf::Texture& texture = Stellar::AssetManager::GetTexture("Path/ToYour/Texture.png");
sf::Font& font = Stellar::AssetManager::GetFont("Path/ToYour/Font.ttf");
sf::SoundBuffer& soundBuffer = Stellar::AssetManager::GetSoundBuffer("Path/ToYour/Sound.ogg");
sf::Music& music = Stellar::AssetManager::GetMusic("Path/ToYour/Music.ogg");
```

> [!NOTE]
> All of your assets need to be in the `/Assets` folder for it to be picked up by the AssetManager.\
> Knowing this, you don't need to specify `Assets/` every time when using it as it'll already look in there by default.