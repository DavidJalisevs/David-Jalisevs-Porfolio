#include <Events.h>

#include "IdleCheckDaggerState.h"

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* IdleCheckDaggerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("IdleCheckDaggerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("IdleCheckDaggerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("IdleCheckDaggerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void IdleCheckDaggerState::update(Player& player) 
{
	DEBUG_MSG("CheckDaggerState -> IdleState");
	if (m_clock.getElapsedTime().asSeconds() > 3.3f)
	{
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new IdlePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void IdleCheckDaggerState::enter(Player& player)
{
	DEBUG_MSG("Entering DaggerCheckState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6452, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6829, 0, 377, 451));
	player.getAnimatedSprite().addFrame(sf::IntRect(6075, 451, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6452, 451, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6829, 451, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6075, 902, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6452, 902, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6829, 902, 377, 451));
	//player.getAnimatedSprite().addFrame(sf::IntRect(6075, 1353, 377, 451));


	player.getAnimatedSprite().setTime(seconds(3.0f));
}
void IdleCheckDaggerState::exit(Player& player)
{
	DEBUG_MSG("Exiting DaggerCheckState");
}