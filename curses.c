#include <ncurses.h>

int main(void)
{
	initscr();
	printw("Hello world!!\n");
	getch();
	endwin();

	return (0);
}
