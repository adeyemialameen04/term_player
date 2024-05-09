#include "term_player.h"
#include <ncurses.h>
#include "audio.h"

static void print_options(music_table_t *ht, int curr_opt)
{
    int i, j = 1;
    music_file_t *tmp;

    for (i = 0; i < (int)ht->size; i++)
    {
        tmp = ht->array[i];
        while (tmp != NULL)
        {
            if (i == curr_opt)
            {
                attron(A_REVERSE);
                printw(" > (%d) %s\n", j, tmp->filename);
                attroff(A_REVERSE);
            }
            else
            {
                printw("   (%d) %s\n", j, tmp->filename);
            }
            tmp = tmp->next;
            j++;
        }
    }
}

void select_options(music_table_t *ht)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int curr_opt = 0;
    int ch;
    playback_t ctx = {0};

    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
        case KEY_UP:
            curr_opt = (curr_opt == 0) ? 0 : curr_opt - 1;
            break;
        case KEY_DOWN:
            curr_opt++;
            break;
        case '\n':
        {
            clear();
            int i, index = 0;
            music_file_t *selected = NULL;
            for (i = 0; i < (int)ht->size; i++)
            {
                music_file_t *tmp = ht->array[i];
                while (tmp != NULL)
                {
                    if (index == curr_opt)
                    {
                        selected = tmp;
                        break;
                    }
                    index++;
                    tmp = tmp->next;
                }
                if (selected != NULL)
                    break;
            }
            if (selected != NULL)
            {
                printw("Currently Playing: %s\n", selected->filename);
                play(selected->filename, &ctx);
            }
            break;
        }
        default:
            break;
        }

        clear();
        print_options(ht, curr_opt);
        refresh();
    }

    endwin();
}
