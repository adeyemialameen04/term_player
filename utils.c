#include "term_player.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * enableCursor - Enables the terminal cursor.
 */
void enableCursor(void)
{
	printf("\e[?25h");
	fflush(stdout);
}

/**
 * disableCursor - Disable the terminal cursor.
 */
void disableCursor(void)
{
	printf("\e[?25l");
	fflush(stdout);
}

/**
 * clearscreen - Clears the terminal screen.
 */
void clearscreen(void)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/**
 * join_path - Joins a dir and a filname path together.
 * @dir: The directory.
 * @filename: The filename.
 * @ht: Hashtable.
 * Return: The fullpath joined.
 */
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
		fullpath = strdup(filename);

	return (fullpath);
}

/**
 * is_music - Checks whether a file is a music file.
 * @filename: The file to be checked.
 * Return: Int.
 */
int is_music(const char *filename)
{
	const char *ext = strrchr(filename, '.');

	if (ext != NULL)
	{
		if (strcmp(ext, ".mp3") == 0 || strcmp(ext, ".wav") == 0)
			return (1);
	}

	return (0);
}

/**
 * printf_colour - Prints in colour.
 * @colour_code: The colour code to be printed.
 * @format: What to be printed.
 */
void printf_colour(int colour_code, const char *format, ...);
void printf_colour(int colour_code, const char *format, ...)
{
	va_list args;

	printf("\033[%dm", colour_code);

	va_start(args, format);
	vprintf(format, args);
	va_end(args);

	printf("\033[0m");
}
