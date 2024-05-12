#include "term_player.h"

/**
 * hash_djb2 - Hashes a str into.
 * @str: The str to be hashed.
 * Return: A hashed integer.
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return (hash);
}

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
