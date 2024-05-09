#include "term_player.h"

int init_colors(void)
{
  if (start_color() != ERR)
  {
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    return 1;
  }
  return 0;
}

WINDOW *create_music_selection(music_table_t *ht)
{
  int y, x, max_len = 0;
  music_file_t *curr;
  WINDOW *win = newwin(LINES - 5, COLS - 10, 2, 5);
  wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

  // Find longest filename
  for (unsigned int i = 0; i < ht->size; i++) {
	curr = ht->array[i];
	while (curr != NULL) {
	  max_len = (max_len < strlen(curr->filename)) ? strlen(curr->filename) : max_len;
	  curr = curr->next;
	}
  }

  // Print music list
  y = 1;
  curr = ht->array[0];
  int selected_index = 0;
  while (curr != NULL && y < LINES - 7) {
	wattron(win, (selected_index == 0) ? COLOR_SELECTED : COLOR_NORMAL);
	mvwprintw(win, y, 1, "%-*s", max_len, curr->filename);
	wattroff(win, (selected_index == 0) ? COLOR_SELECTED : COLOR_NORMAL);
	curr = curr->next;
	y++;
  }
  wrefresh(win);

  return win;
}
