#include <Events.h>

#include <DoubleJumpState.h>
#include <DiedPlayerState.h>
#include <JumpAttackPlayerState.h>
#include <JumpThrowAttackPlayerState.h>
#include <GlidePlayerState.h>


PlayerState* DoubleJumpState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("DoubleJumpState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("DoubleJumpState -> JumpAttackPlayerState");
		return new JumpAttackPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("DoubleJumpState -> JumpThrowAttackPlayerState");
		return new JumpThrowAttackPlayerState();
	}
	
	return nullptr;
}

void DoubleJumpState::update(Player& player)
{
    DEBUG_MSG("DoubleJumpPlayerState -> GlidePlayerState");
    if (m_clock.getElapsedTime().asSeconds() > 2.0f) {
        PlayerState* temp = player.getPlayerState();
        PlayerState* state = new GlidePlayerState();
        player.getPlayerState()->exit(player);
        player.setPlayerState(state);
        player.getPlayerState()->enter(player);
        delete temp;
    }
}

void DoubleJumpState::enter(Player& player)
{
    DEBUG_MSG("Entering DoubleJumpPlayerState");
    player.getAnimatedSprite().clearFrames();

    player.getAnimatedSprite().setPlayed(false);
    player.getAnimatedSprite().setLooped(false);

	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 3205, 362, 483));
 

    player.getAnimatedSpriteFrame().setTime(seconds(0.03f));
}

void DoubleJumpState::exit(Player& player)
{
	DEBUG_MSG("Exiting DoubleJumpState");

}
