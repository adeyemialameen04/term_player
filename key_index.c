#include "term_player.h"

/**
 * key_index - Create a new keey for the slot.
 * @key: The key for the hashed.
 * @size: The size of the ht.
 * Return: an index within the size of the ht.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hashed_key = hash_djb2(key) % size;

	return (hashed_key);
}
