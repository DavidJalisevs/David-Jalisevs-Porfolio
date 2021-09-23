#ifndef IDLE_CHECK_DAGGER_STATE_H
#define IDLE_CHECK_DAGGER_STATE_H

#include <Player.h>
#include <PlayerState.h>
#include <SFML/Graphics.hpp>

class IdleCheckDaggerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player& player);
	virtual void enter(Player& player);
	virtual void exit(Player& player);
private:
	sf::Clock m_clock;
};

#endif