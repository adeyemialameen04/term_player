#include "term_player.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * create_node - Creates a node to be inserted.
 * @filename: The thing to be inserted.
 * @directory_path: The path of the file.
 * Return: A single node.
 */
static music_file_t *create_node(char *filename, char *directory_path);
static music_file_t *create_node(char *filename, char *directory_path)
{
	music_file_t *new_node = malloc(sizeof(music_file_t));
	char *fullpath;

	if (new_node == NULL)
	{
		fprintf(stderr, "Unable to create a new node\n");
		return (NULL);
	}

	if (*filename == '\0')
	{
		free(new_node);
		fprintf(stderr, "Was not able to create node (err: filename/key is NULL)\n");
		return (NULL);
	}

	new_node->filename = strdup(filename);
	if (new_node->filename == NULL)
	{
		free(new_node);
		fprintf(stderr, "Unable to duplicate the key\n");
		return (NULL);
	}

	if (directory_path != NULL)
	{
		fullpath = malloc(strlen(directory_path) + strlen(filename) + 1);
		if (fullpath == NULL)
		{
			fprintf(stderr, "Unale to allocate memory for fullpath\n");
			free(new_node->filename);
			free(new_node);
			return (NULL);
		}
		sprintf(fullpath, "%s/%s", directory_path, filename);
	}
	else
	{
		fullpath = strdup(filename);
		if (fullpath == NULL)
		{
			fprintf(stderr, "Unale to allocate memory for fullpath\n");
			free(new_node->filename);
			free(new_node);
			return (NULL);
		}
	}

	if (stat(fullpath, &new_node->st) != 0)
	{
		free(new_node->filename);
		free(new_node);
		free(fullpath);
		fprintf(stderr, "Unable to get stat file key\n");
		return (NULL);
	}

	return (new_node);
}

/**
 * insert - Inserts an elemnt into the hashtable.
 * @ht: The hashtable to be inserted into.
 * @filename: The filename to be inserted.
 * Return: 1 on success 0 on failure.
 */
int insert(music_table_t *ht, char *filename);
int insert(music_table_t *ht, char *filename)
{
	unsigned long int idx;
	music_file_t *curr, *new_node, *prev;

	if (ht == NULL || *filename == '\0')
	{
		fprintf(stderr, "Error in insert ht/key is NULL\n");
		exit(EXIT_FAILURE);
	}

	idx = key_index((const unsigned char *)filename, ht->size);
	printf("Idx for everyone is (%ld)\n", idx);
	curr = ht->array[idx];
	while (curr != NULL)
	{
		if (strcmp(curr->filename, filename) == 0)
		{
			if (stat(filename, &curr->st) != 0)
			{
				fprintf(stderr, "Unable to get stat file key\n");
				return (0);
			}
			printf("Any duplicates?\n");
			return (1);
		}
		curr = curr->next;
	}

	new_node = create_node(filename, ht->directory);
	if (new_node == NULL)
	{
		fprintf(stderr, "Error creating a newnode (create)\n");
		exit(EXIT_FAILURE);
	}
	new_node->next = ht->array[idx];
	ht->array[idx] = new_node;

	curr = ht->head;
	while (curr != NULL && strcmp(curr->filename, filename) < 0)
	{
		prev = curr;
		curr = curr->snext;
	}

	if (prev == NULL)
	{
		new_node->snext = ht->head;
		if (ht->head != NULL)
			ht->head->sprev = new_node;

		ht->head = new_node;
	}
	else
	{
		new_node->sprev = prev;
		new_node->snext = prev->snext;
		if (prev->snext != NULL)
			prev->snext->sprev = new_node;

		prev->snext = new_node;
	}

	if (new_node->snext == NULL)
		ht->tail = new_node;

	return (1);
}
