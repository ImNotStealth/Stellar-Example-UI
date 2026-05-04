#ifndef STATE_ASYNC_EXAMPLE_H
#define STATE_ASYNC_EXAMPLE_H

#include <Stellar/Stellar.h>

class StateAsyncExample : public Stellar::GameState
{
public:
	StateAsyncExample()
		: GameState("Async Example") {}

	void Load() override;
	void Update(float _deltaTime) override;

private:
	Stellar::Button buttonBack;
};

#endif