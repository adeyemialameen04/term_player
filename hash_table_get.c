#include "term_player.h"

music_file_t *hash_table_get(music_table_t *ht, char *key)
{
	unsigned int idx;
	music_file_t *curr;

	if (ht == NULL || *key == '\0')
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	curr = ht->array[idx];

	while (curr != NULL)
	{
		if (strcmp(curr->filename, key) == 0)
			return (curr);

		curr = curr->next;
	}

	return (NULL);
}
