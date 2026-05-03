# Language
Allows you to localize your game by reading a text file (this one's important!)

# Samples
[Here](../x64/Debug/Game/Assets/Lang/) you'll find two files, `en_US.lang` and `fr_FR.lang`.\
Take a look in there and follow the format. For example, if you want to add a sword, you'd add:
```
In fr_FR.lang
weapons.sword=Épée

In en_US.lang
weapons.sword=Sword
```

If you need to mix in a value from your code with the translation, you can add `{}` in your translation.
```
gameover.score=Score: {}
```

If you want to read a translation from your code:
```c++
text.setString(Stellar::Language::Get().Translate("weapons.sword"));

// If you need to format a value from your code, you'd use Format instead of Translate
text.setString(Stellar::Language::Get().Format("gameover.score", std::to_string(123)));
```

# Adding a new language
Start by creating a new file for your language in `/Assets/Lang/`.\
Go into the Language [header](../Stellar/src/Stellar/Core/Language.h) file and add your language in the `LangType` enum. Next, head into the [source](../Stellar/src/Stellar/Core/Language.cpp) file and add your language to the two switches found in `LangEnumToStr` and `LangStrToEnum` functions.\
If you want to add your language to the DebugOverlay, you can modify it [here](../Stellar/src/Stellar/Debug/DebugOverlay.cpp).

# Setting the current language
An example of setting the language can be found [here](Settings.md).