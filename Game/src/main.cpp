#include <Stellar/Stellar.h>

#ifdef STELLAR_DEBUG
#include "Debug/ToolExample.h"
#endif

#include <Stellar/Render/GameSplash.h>
#include "Menu/StateMainMenu.h"

using namespace Stellar;

int main()
{
	Game::Get().SetSettings({ "Stellar Game" });
#ifndef STELLAR_DEBUG
	Game::Get().SetState<GameSplash<StateMainMenu>>();
#else
	Game::Get().SetState<StateMainMenu>();
#endif
	Game::Get().Run();
	return 0;
}