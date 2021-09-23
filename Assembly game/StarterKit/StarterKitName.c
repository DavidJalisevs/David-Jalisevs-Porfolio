#include <stdbool.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <uzebox.h>
#include <defines.h>

#include "data/font-6x12-full.inc"
#include "StarterKit.h"

int main(){
	//Set font and tiles to be used, and call prior to ClearVram();
	SetFontTable(font);

	//Clear the screen (fills Vram with tile zero)
	ClearVram();

	PrintChar(10,10,'D');
	PrintChar(11,10,'A');
	PrintChar(12,10,'V');
	PrintChar(13,10,'I');
	PrintChar(14,10,'D');
	PrintChar(15,10,' ');
	PrintChar(16,10,' ');
	PrintChar(17,10,' ');
	PrintChar(18,10,' ');
	PrintChar(19,10,' ');
	PrintChar(20,10,' ');
	PrintChar(21,10,' ');
	PrintChar(22,10,' ');
	PrintChar(23,10,' ');
	PrintChar(24,10,' ');
	PrintChar(25,10,' ');
	PrintChar(26,10,' ');

	while(1)
	{
		startgame();
	}
}
