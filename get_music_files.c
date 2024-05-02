#include "term_player.h"

int is_music(const char *filename)
{
	const char *ext = strrchr(filename, '.');
	
	if (ext != NULL)
	{
		if (strcmp(ext, ".mp3") == 0 || strcmp(ext, ".wav") == 0)
		{
			return (1);
		}
	}

	return (0);
}

char *get_music_files(void)
{
	DIR *dir;
	struct dirent *entry;
	int count = 0;
	FILE *fd;
	char *filename = "musics.txt";

	dir = opendir(".");
	if (dir == NULL)
	{
		fprintf(stderr, "Error opening dir\n");
		fclose(fd);
		exit(EXIT_FAILURE);	
	}

	fd = fopen(filename, "a+");
	if (fd == NULL)
	{
		fprintf(stderr, "Was not able to create file\n");
		closedir(dir);
		exit(EXIT_FAILURE);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		printf("Name are === ---%s---\n", entry->d_name);
		if (is_music(entry->d_name))
		{
			printf("Here too ARE U FFF BLIND? ...\n");
			count++;
			fprintf(fd, "%s\n", entry->d_name);
		}
	}

	closedir(dir);
	fclose(fd);

	return (filename);
}
