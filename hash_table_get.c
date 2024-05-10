#include "term_player.h"

music_file_t *hash_table_get(music_table_t *ht, char *key)
{
	music_file_t *curr;

	if (ht == NULL || *key == '\0')
		return (NULL);

	curr = ht->head;

	while (curr != NULL)
	{
		if (strcmp(curr->filename, key) == 0)
			return (curr);

		curr = curr->next;
	}

	return (NULL);
}
