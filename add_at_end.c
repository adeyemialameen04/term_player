#include "term_player.h"
#include <string.h>

void add_at_end(music_file_t **head, char *filename)
{
	music_file_t *new_node = malloc(sizeof(music_file_t));
	music_file_t *curr;

	if (new_node == NULL)
		return;
	strcpy(new_node->filename, filename);
	new_node->next = NULL;

	if (*head == NULL)
	{
		new_node->next = *head;
		new_node->prev = NULL;
		*head = new_node;
		return;
	}
	
	curr = *head;
	while (curr->next != NULL)
		curr = curr->next;

	curr->next = new_node;
	new_node->prev = curr;

	return;
}
