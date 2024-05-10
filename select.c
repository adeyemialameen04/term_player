#include "term_player.h"
#include "audio.h"
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
    unsigned int i, j;
    music_file_t *tmp;

    printf("Select a music file:\n");

    j = 0;  // Initialize a counter for the overall index
    for (i = 0; i < ht->size; i++)
    {
        tmp = ht->array[i];
        while (tmp != NULL)
        {
            if (j == *selected_option)
                printf("> ");
            else
                printf(" ");
            printf("%s\n", tmp->filename);
            tmp = tmp->next;
            j++;
        }
    }
}

music_file_t *select_music_file(music_table_t *ht) {
    enableRawMode();
    int selected_option = 0;
    int max_options = 0;

    for (unsigned int i = 0; i < ht->size; i++)
    {
        music_file_t *tmp = ht->array[i];

        while (tmp != NULL)
        {
            max_options++;
            tmp = tmp->next;
        }
    }

    while (1)
    {
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
                    selected_option = (selected_option == 0) ? max_options - 1 : selected_option - 1;
                    break;
                case 'B':
                    selected_option = (selected_option == max_options - 1) ? 0 : selected_option + 1;
                    break;
            }
        }
        else if (ch == '\n')
        {
            int curr_index = 0;
            for (unsigned int i = 0; i < ht->size; i++)
            {
                music_file_t *curr = ht->array[i];
                while (curr != NULL)
                {
                    if (curr_index == selected_option)
                    {
                        printf("Selected is %s\n", curr->filename);
                        return (curr);
                    }
                    curr_index++;
                    curr = curr->next;
                }
            }
            printf("It's a prank lol\n");
            break;
        }
    }

    return (NULL);
}
