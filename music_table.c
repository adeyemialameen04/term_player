#include <stdio.h>
#include <stdlib.h>
#include "term_player.h"

/**
 * create_ht - Allocates memory for an hashtable.
 * @size: The size the hashtable should be.
 * Return: A new hash_table.
 */
music_table_t *create_ht(unsigned int size)
{
	int i;
	music_table_t *ht = malloc(sizeof(music_table_t));

	if (ht == NULL)
	{
		fprintf(stderr, "Unable to create ht\n");
		exit(EXIT_FAILURE);
	}

	ht->array = malloc(sizeof(music_file_t *) * size);
	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	ht->size = size;
	ht->musics_file = "musics.txt";
	ht->directory = NULL;
	ht->tail = NULL;
	ht->head = NULL;

	return (ht);
}

/**
 * build_dll - Builds the hashtable.
 * @ht: The hashtable.
 */
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

/**
 * hash_table_get - Gets a value from an hash_table based on key.
 * @ht: The hashtable to search from.
 * @key: The key to be found.
 * Return: The key/value pair found.
 */
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

/**
 * free_ht - Frees an hashtable.
 * @ht: The hashtable to be freed.
 */
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
/**
 * print_ht - Prints the hashtable.
 * @ht: The hashtable to be printed.
 */
void print_ht(music_table_t *ht)
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
