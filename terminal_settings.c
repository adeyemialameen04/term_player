#include "term_player.h"
#include <termios.h>
#include <sys/ioctl.h>

/**
 * enableRawMode - Enables raw mode in the terminal.
 */
void enableRawMode(void)
{
	struct termios term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fileno(stdin), TCSANOW, &term);
}

/**
 * disableRawMode - Disables raw mode in the terminal.
 */
void disableRawMode(void)
{
	struct termios term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag |= ICANON | ECHO;
	tcsetattr(fileno(stdin), TCSANOW, &term);
}

/**
 * kbhit - A custom keyboard hit.
 * Return: Bool.
 */
bool kbhit(void)
{
	struct termios term, term2;
	int byteswaiting;

	tcgetattr(0, &term);

	term2 = term;

	term2.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term2);

	ioctl(0, FIONREAD, &byteswaiting);

	tcsetattr(0, TCSANOW, &term);

	return (byteswaiting > 0);
}
