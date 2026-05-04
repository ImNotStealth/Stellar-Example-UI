#include "StateAsyncExample.h"

#include "StateMainMenu.h"
#include <chrono>
#include <thread>

void StateAsyncExample::Load()
{
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

	std::cout << "Sleeping for 5 seconds to simulate loading..." << std::endl;
    std::this_thread::sleep_for(5s);
}

void StateAsyncExample::Update(float _deltaTime)
{
    std::cout << "Loading finished after 5 seconds, returning to MainMenu!" << std::endl;
    Stellar::Game::Get().SetState<StateMainMenu>();
}
