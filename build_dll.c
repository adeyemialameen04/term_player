#include <stdio.h>
#include "term_player.h"

void build_dll(music_table_t *ht)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t chars_read;
	FILE *fd;

	if (*ht->musics_file == '\0')
		exit(EXIT_FAILURE);

	fd = fopen(ht->musics_file, "r");
	if (fd == NULL)
	{
		fprintf(stderr, "Unable to open file for building\n");
		exit(EXIT_FAILURE);
	}

	while ((chars_read = getline(&line, &size, fd)) != -1)
	{
		char *str = line;
		int len = strcspn(str, "\n");

		str[len] = '\0';
		insert(ht, str);
	}

	free(line);
	fclose(fd);
}
