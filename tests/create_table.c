#include "term_player.h"

music_table_t *create_ht(unsigned int size)
{
	int i;
	music_table_t *ht = malloc(sizeof(music_table_t));

	if (ht == NULL)
		return (NULL);

	ht->array = malloc(sizeof(music_file_t *) * size);
	for (i = 0; i < size; i++)
	{
		ht->array[i] = NULL;
	}

	ht->size = size;
	return (ht);
}
