#include "term_player.h"
#include <stdio.h>

/**
 * get_music_files - Gets music files and read them into a txt file.
 * @filename: The filename to read into.
 * @path: The path of the files.
 * Return: the amount of music files gotten.
 */
int get_music_files(char *filename, char *path);
int get_music_files(char *filename, char *path)
{
	DIR *dir;
	struct dirent *entry;
	int count = 0;
	FILE *fd;

	dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "Error opening dir\n");
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	fd = fopen(filename, "w+");
	if (fd == NULL)
	{
		fprintf(stderr, "Was not able to create file\n");
		closedir(dir);
		exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (is_music(entry->d_name))
		{
			fprintf(fd, "%s\n", entry->d_name);
			count++;
		}
	}

	if (count == 0)
	{

		printf_colour(31, "No music files detected\n");
		printf_colour(31, "Add music files to the current "
						  "directory to use term_player\n");
		closedir(dir);
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	closedir(dir);
	fclose(fd);

	return (count);
}
