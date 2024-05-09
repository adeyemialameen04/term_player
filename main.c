#include "term_player.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	music_table_t *ht;
	music_file_t *curr;
	int size;
	int path;
	char *path_ptr = NULL;
	char *real;
	size_t n = 0;
	ssize_t chars_read;

	printf("Press (0) to read the music files, and (1) to read from another directory\n");
	scanf("%d", &path);

	while(getchar() != '\n');
	if (path == 0)
	{
		size = get_music_files("musics.txt", ".");
	}
	else if (path == 1)
	{
		printf("Enter directory path: ");
		chars_read = getline(&path_ptr, &n, stdin);
		if (chars_read > 0 && path_ptr[chars_read - 1] == '\n')
			path_ptr[chars_read - 1] = '\0';
		size = get_music_files("musics.txt", path_ptr);
	}
	else
	{
		printf("Wrong command dumbass\n");
		exit (EXIT_FAILURE);
	}


	ht = create_ht(size);
	ht->directory = strdup(path_ptr);
	build_dll(ht);
	curr = hash_table_get(ht, "happy.mp3");

	print_dll(ht);
	if (curr != NULL)
		printf("CURR IS %s\n", curr->filename);
	else
		printf("Curr is also NULL lol\n");

	if (curr->next != NULL)
		printf("CURR->NEXT IS %s\n", curr->next->filename);
	else
		printf("Curr->NEXT is also NULL lol\n");
	
	if (curr->next->next != NULL)
		printf("Wow wth is now wrong %s\n", curr->next->next->filename);
	else
		printf("I got too happy lol\n");
    /* int selected_index = select_music_file(ht);

	// Check if a music file was selected
	if (selected_index >= 0)
		printf("Selected file: %s\n", ht->array[selected_index]->filename);
	else
		printf("No file selected\n");
	*/

	free_ht(ht);
	return (1);
}
