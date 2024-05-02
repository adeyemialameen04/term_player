#include "term_player.h"
#include <stdio.h>

int main(void)
{
	music_file_t *head = NULL;

	char *ret_file_name = get_music_files();
	build_dll(&head, ret_file_name);

	print_dll(head);
	return (1);
}
