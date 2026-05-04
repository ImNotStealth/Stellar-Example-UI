#include <Stellar/Stellar.h>

#ifdef STELLAR_DEBUG
#include "Debug/ToolPress.h"
#include "Debug/ToolStructure.h"
#endif

#include <Stellar/Render/GameSplash.h>
#include "Menu/StateMainMenu.h"

using namespace Stellar;

int main()
{
	Game::Get().SetSettings({ "Godbreak" });
	Game::Get().SetState<GameSplash<StateMainMenu>>();
	Game::Get().Run();
	return 0;
}