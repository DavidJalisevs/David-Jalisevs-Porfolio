#include "Idle.h"


void Idle::jumping(Animation* a)
{
	std::cout << "Player just did a jump!" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation* a)
{
	std::cout << "Player is now Climbing!" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}