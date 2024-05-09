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


void print_menu(music_table_t *ht, int selected_option) {
    printf("Select a music file:\n");

    // Print music file options
    for (unsigned int i = 0; i < ht->size; i++) {
        music_file_t *tmp = ht->array[i];
        while (tmp != NULL) {
            if (i == selected_option) {
                if (tmp == ht->array[i]) {
                    printf("> "); // Print ">" symbol only for the first file in the linked list
                } else {
                    printf("  "); // Print spaces for subsequent files in the same linked list
                }
            } else {
                printf("  "); // Print spaces for non-selected options
            }
            printf("%s\n", tmp->filename);
            tmp = tmp->next;
        }
    }
}

int select_music_file(music_table_t *ht) {
    enableRawMode();
    int selected_option = 0;

    while (1)
    {
        printf("\033[2J\033[H");
        print_menu(ht, selected_option);
        char ch = getchar();

        if (ch == 'q')
            break;

        if (ch == '\033')
        {
            getchar();

            switch (getchar())
            {
                case 'A':
                    selected_option = (selected_option == 0) ? ht->size - 1 : selected_option - 1;
                    break;
                case 'B':
                    selected_option = (selected_option == ht->size - 1) ? 0 : selected_option + 1;
                    break;
            }
        }
        else if (ch == '\n')
        {
            music_file_t *curr = ht->array[selected_option];

            if (curr != NULL)
                printf("Selected is %s\n", curr->filename);
            else
                printf("Its a prank lol\n");
            break;
        }
    }

    disableRawMode();
    return -1;
}
