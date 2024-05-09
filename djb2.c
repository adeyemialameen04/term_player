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
