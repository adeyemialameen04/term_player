#include "term_player.h"
#include <stdio.h>


void print_dll(music_file_t *head)
{
	music_file_t *curr;

	if (head == NULL)
	{
		fprintf(stderr, "The list is empty\n");
		exit(EXIT_FAILURE);
	}

	curr = head;

	while (curr != NULL)
	{
		printf("======== %s =======\n", curr->filename);
		curr = curr->prev;
	}
}
