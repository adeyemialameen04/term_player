#include "term_player.h"

void build_dll(music_file_t **head, char *filename)
{
	char *line;
	size_t size = 0;
	ssize_t chars_read;
	FILE *fd;

	if (*filename == '\0')
		exit(EXIT_FAILURE);
		

	fd = fopen(filename, "r");
	if (fd == NULL)
	{
		fprintf(stderr, "Unable to open file for building\n");
		exit(EXIT_FAILURE);
	}

	while ((chars_read = getline(&line, &size, fd)) != -1)
	{
		add_at_end(head, line);
	}

	free(line);
	fclose(fd);
}
