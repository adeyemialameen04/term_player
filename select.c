#include "term_player.h"
#include <stdio.h>
#include <termios.h>

static void enableRawMode() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

static void disableRawMode() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &term);
}

void print_menu(music_table_t *ht, int *selected_option)
{
    unsigned int i = 0;
    music_file_t *tmp = ht->head;

    printf("Select a music file:\n");

    while (tmp != NULL)
    {
        if (i == *selected_option)
            printf("\033[35m>\033[0m \033[32m%s\033[0m\n", tmp->filename);
        else
            printf(" \033[32m%s\033[0m\n", tmp->filename);
        tmp = tmp->snext;
        i++;
    }
}

music_file_t *select_music_file(music_table_t *ht)
{
    enableRawMode();
    int selected_option = 0;
    int max_options = 0;
    music_file_t *tmp = ht->head;
    music_file_t *selected = NULL;

    while (tmp != NULL)
    {
        max_options++;
        tmp = tmp->snext;
    }

    disableCursor();
    clearscreen();
    while (1)
    {
        clearscreen();
        printf("\033[2J\033[H");
        print_menu(ht, &selected_option);
        char ch = getchar();

        if (ch == 'q')
            break;
        if (ch == '\033')
        {
            getchar();
            switch (getchar())
            {
            case 'A':
                if (selected != NULL && selected->sprev != NULL)
                    selected = selected->sprev;
                else if (selected_option == 0)
                    selected_option = max_options - 1;
                else
                    selected_option--;
                break;
            case 'B':
                if (selected != NULL && selected->snext != NULL)
                    selected = selected->snext;
                else if (selected_option == max_options - 1)
                    selected_option = 0;
                else
                    selected_option++;
                break;
            case 'C':
                if (selected != NULL && selected->snext != NULL)
                    selected = selected->snext;
                break;
            case 'D':
                if (selected != NULL && selected->sprev != NULL)
                    selected = selected->sprev;
                break;
            }
        }
        else if (ch == '\n')
        {
            tmp = ht->head;
            for (int i = 0; i < selected_option; i++)
                tmp = tmp->snext;

            selected = tmp;
            printf("Selected is %s\n", selected->filename);
            return selected;
        }
    }
    enableCursor();

    return NULL;
}
