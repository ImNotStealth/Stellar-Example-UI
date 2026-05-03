# SoundHandler
A utility class to play sound effects.\
Depending on the sound type specified, the volume will adjust depending on the user's settings.\
The sound passed in will automagically be handled by the [AssetManager](AssetManager.md) so no need to load it beforehand.

# Sample
```c++
Stellar::SoundHandler::Get().Play("Sounds/Test.ogg", Stellar::SoundType::SFX);
```

> [!NOTE]
> By default, there is `SFX`, `UI` and `NONE` as SoundTypes. Specifying `NONE` will only adjust the volume depending on the Master volume setting.