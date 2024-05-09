#include "term_player.h"
#include <stdio.h>

void print_dll(music_table_t *ht)
{
	music_file_t *curr;
	unsigned long int i;
	int is_first = 1;

	if (ht == NULL)
	{
		fprintf(stderr, "The list is empty\n");
		exit(EXIT_FAILURE);
	}

	printf("{");
	for (i = 0; i < ht->size; i++)
	{
		curr = ht->array[i];
		while (curr != NULL)
		{
			double size_MB = (double)curr->st.st_size / (1024 * 1024);

			if (is_first)
				is_first = 0;
			else
				printf(", ");
			printf("'%s': %.2fMB", curr->filename, size_MB);
			curr = curr->next;
		}
	}
	printf("}\n");
}
