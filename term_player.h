#ifndef _TERM_PLAYER_H_
#define _TERM_PLAYER_H_
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ncurses.h"
#define COLOR_NORMAL  PAIR(1)
#define COLOR_SELECTED PAIR(2)
typedef struct music_file
{
  char *filename; /* KEY */
  struct stat st;
  struct music_file *prev;
  struct music_file *next;
} music_file_t;

typedef struct music_table
{
  unsigned int size;
  char *musics_file;
  char *directory;
  music_file_t **array;
} music_table_t;

music_table_t *create_ht(unsigned int size);
void print_dll(music_table_t *ht);
void build_dll(music_table_t *ht);
int is_music(const char *filename);
int insert(music_table_t *ht, char *filename);
int get_music_files(char *filename, char *path);
unsigned long int hash_djb2(const unsigned char *str);
unsigned long int key_index(const unsigned char *key, unsigned long int size);
void free_ht(music_table_t *ht);
music_file_t *hash_table_get(music_table_t *ht, char *key);
music_file_t *select_music_file(music_table_t *ht);

#endif /* _TERM_PLAYER_H_ */
