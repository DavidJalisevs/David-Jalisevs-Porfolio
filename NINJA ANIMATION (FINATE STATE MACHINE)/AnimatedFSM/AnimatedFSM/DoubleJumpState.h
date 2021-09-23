
#ifndef DOUBLE_JUMP_STATE_H
#define DOUBLE_JUMP_STATE_H

#include <Player.h>
#include <PlayerState.h>

class DoubleJumpState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
private:
	sf::Clock m_clock;
};

#endif





