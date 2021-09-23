
#include "Animation.h"
#include "Climbing.h"
#include "Idle.h"
#include "Jumping.h"
#include "State.h"

Animation::Animation()
{	current = new Idle(); }

void Animation::idle()
{	current->idle(this);}

void Animation::jumping()
{	current->jumping(this);}

void Animation::climbing()
{	current->climbing(this); }