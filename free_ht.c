#include "term_player.h"
#include <stdlib.h>

void free_ht(music_table_t *ht)
{
	unsigned int i;

	for (i = 0; i < ht->size; i++)
	{
		music_file_t *curr = ht->array[i];

		while (curr != NULL)
		{
			music_file_t *next = curr->next;
			free(curr->filename);
			free(curr);
			curr = next;
		}
	}

	free(ht->array);
	free(ht);
}
