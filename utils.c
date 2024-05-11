#include "term_player.h"
#include <stdio.h>
#include <termios.h>

void enableCursor(void)
{
	printf("\e[?25h");
	fflush(stdout);
}

void disableCursor(void)
{
	printf("\e[?25l");
	fflush(stdout);
}
