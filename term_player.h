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
  struct music_file *sprev;
  struct music_file *snext;
  struct music_file *next;
} music_file_t;

typedef struct music_table
{
  unsigned int size;
  char *musics_file;
  char *directory;
  music_file_t **array;
  music_file_t *head;
  music_file_t *tail;
} music_table_t;

/* HASHTABLE */
music_table_t *create_ht(unsigned int size);
void print_dll(music_table_t *ht);
music_file_t *hash_table_get(music_table_t *ht, char *key);
void build_dll(music_table_t *ht);
int insert(music_table_t *ht, char *filename);
unsigned long int hash_djb2(const unsigned char *str);
unsigned long int key_index(const unsigned char *key, unsigned long int size);
void free_ht(music_table_t *ht);
/* HASHTABLE END */

/* MUSIC */
music_file_t *select_music_file(music_table_t *ht);
int is_music(const char *filename);
int get_music_files(char *filename, char *path);
/* MUSIC END */

/* UTILS */
void clearscreen(void);
void disableCursor(void);
void enableCursor(void);
void print_author(void);
char *join_path(char *dir, char *filename, music_table_t *ht);
void print_player(music_file_t *selected);
/* UTILS END */

#endif /* _TERM_PLAYER_H_ */
