#include "term_player.h"
#include <stdio.h>
#include <termios.h>
#include <termios.h>
#include <sys/ioctl.h>

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

void clearscreen(void)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

bool kbhit(void) 
{ 
	struct termios term; 
	tcgetattr(0, &term); 
 
	struct termios term2 = term; 
	term2.c_lflag &= ~ICANON; 
	tcsetattr(0, TCSANOW, &term2); 
 
	int byteswaiting; 
	ioctl(0, FIONREAD, &byteswaiting); 
 
	tcsetattr(0, TCSANOW, &term); 
 
	return byteswaiting > 0; 
}

char *join_path(char *dir, char *filename, music_table_t *ht)
{
	char *fullpath;

	if (dir != NULL)
	{
		fullpath = malloc(strlen(dir) + strlen(filename) + 2);
		if (fullpath == NULL)
		{
			fprintf(stderr, "Unable to allocate memory for fullpath\n");
			free_ht(ht);
			free(dir);
			return (NULL);
		}
		sprintf(fullpath, "%s/%s", dir, filename);
	}
	else
	{
		printf("Are u NULL?\n");
		fullpath = strdup(filename);
	}

	return (fullpath);
}

