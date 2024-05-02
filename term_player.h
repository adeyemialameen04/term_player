#ifndef _TERM_PLAYER_H_
#define _TERM_PLAYER_H_
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

typedef struct music_file {
  char filename[256];
  struct music_file *prev;
  struct music_file *next;
} music_file_t;

/* typedef struct music_table {
  unsigned int size;
  music_file_t **array;
} music_table_t;

music_table_t *create_ht(unsigned int size); */
void add_at_end(music_file_t **head, char *filename); 
void print_dll(music_file_t *head);
void build_dll(music_file_t **head, char *filename);
int is_music(const char *filename);
char *get_music_files(void);

#endif /* _TERM_PLAYER_H_ */
