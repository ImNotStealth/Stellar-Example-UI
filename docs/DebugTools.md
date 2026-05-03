# DebugTools

Useful if you need a tool that is accessible globally (outside of any GameState).\
You can use these tools by building your game in Debug mode and by pressing F1 to show the Debug Overlay.\
An example use case is if you need to change GameState and you haven't yet coded a UI to do so. Or you have some sort of debug level that isn't normally accessible. Or you want to test a system that isn't even dependent on your game. (The ControllerInput tool is a great example of this!)

This should be the expected result: [Gyazo](https://gyazo.com/9870edc46d017e8de450ecbe26ebf6f3)

# Sample

Header:
```c++
#ifndef TOOL_TEST_H
#define TOOL_TEST_H

#include <Stellar/Stellar.h>

class ToolTest : public Stellar::DebugTool
{
public:
    ToolTest()
        : DebugTool("Test Tool") {}

    void UpdateImGui(float _deltaTime) override;
};

#endif
```

Source:
```c++
#include "ToolTest.h"

REGISTER_DEBUG_TOOL(ToolTest)

void ToolTest::UpdateImGui(float _deltaTime)
{
    ImGui::Text("Hey!");
}
```

> [!NOTE]
> Do not forget you must include your tool's header for it to be registered.\
> For example, I always added it in the `main.cpp` file

```c++
#include <Stellar/Stellar.h>

// Only include if in Debug, wouldn't be accessible in Release anyway
#ifdef STELLAR_DEBUG
#include "Debug/ToolExample.h"
#endif

#include "Menu/StateMainMenu.h"

using namespace Stellar;

int main()
{
	Game::Get().SetSettings({ "Stellar Game" });
	Game::Get().SetState<StateMainMenu>();
	Game::Get().Run();
	return 0;
}
```