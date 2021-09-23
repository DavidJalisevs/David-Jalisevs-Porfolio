#include "CRYSTALS.h"

void CRYSTALS::render(sf::RenderWindow &t_window)
{
	if (asteroidDestroyed == true)
	{
		t_window.draw(m_CrystalSprite);
	}
	t_window.draw(CrystText);
}

void CRYSTALS::loadContent(sf::Font &t_font)
{
	m_font = t_font;
	if (!m_crystaltexture.loadFromFile("ASSETS/IMAGES/Crystal.png"))
	{
		std::cout << "COULD NOT LOAD PLAYER TEXTURE" << std::endl;
	}
	m_CrystalSprite.setTexture(m_crystaltexture);
	
	
	
}

void CRYSTALS::update()
{
}

void CRYSTALS::getCrystalPos(sf::Vector2f t_asteroidPos,sf::Vector2f t_crystalSpawn)
{
	

	m_CrystalSprite.getPosition();
	m_CrystalSprite.setPosition(t_asteroidPos);
	if (asteroidDestroyed == true)
	{
		m_CrystalSprite.setPosition(t_crystalSpawn);
	}
	
	CrystText.setFont(m_font);
	CrystText.setCharacterSize(30);
	CrystText.setString("crystals Collected : " + std::to_string(crystalsCollected));
	CrystText.setFillColor(sf::Color::Red);
	CrystText.setPosition(100.0f, 10.0f);

	if (crystalHasBeenCollected == true)
	{
		crystalsCollected++;
		
	}
}
	

void CRYSTALS::setupText()
{

}
