#include "term_player.h"
#include <stdio.h>

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
		printf("No music files detected\n");
		printf("Add music files to the current directory to use term_player\n");
		closedir(dir);
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	closedir(dir);
	fclose(fd);

	return (count);
}
