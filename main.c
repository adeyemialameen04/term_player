#include "audio.h"
#include "term_player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearscreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_author(void)
{
    printf("\033[32m"
           "<!-- .·:'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''':·. -->\n"
           "<!-- : :                         ____                _           _      _                                     : : -->\n"
           "<!-- : :                        / ___|_ __ ___  __ _| |_ ___  __| |    | |__  _   _                           : : -->\n"
           "<!-- : :                       | |   | '__/ _ \\/ _` | __/ _ \\/ _` |    | '_ \\| | | |                          : : -->\n"
           "<!-- : :                       | |___| | |  __/ (_| | ||  __/ (_| |    | |_) | |_| |                          : : -->\n"
           "<!-- : :                        \\____|_|  \\___|\\__,_|\\__\\___|\\__,_|    |_.__/ \\__, |                          : : -->\n"
           "<!-- : :         _    _         _                                   _       _ |___/                     _     : : -->\n"
           "<!-- : :        / \\  | |       / \\   _ __ ___   ___  ___ _ __      / \\   __| | ___ _   _  ___ _ __ ___ (_)    : : -->\n"
           "<!-- : :       / _ \\ | |_____ / _ \\ | '_ ` _ \\ / _ \\/ _ \\ '_ \\    / _ \\ / _` |/ _ \\ | | |/ _ \\ '_ ` _ \\| |    : : -->\n"
           "<!-- : :      / ___ \\| |_____/ ___ \\| | | | | |  __/  __/ | | |  / ___ \\ (_| |  __/ |_| |  __/ | | | | | |    : : -->\n"
           "<!-- : :     /_/   \\_\\_|    /_/   \\_\\_| |_| |_|\\___|\\___|_| |_| /_/   \\_\\__,_|\\___|\\__, |\\___|_| |_| |_|_|    : : -->\n"
           "<!-- : :                                                                           |___/                      : : -->\n"
           "<!-- '·:......................................................................................................:·' -->\n"
           "\033[0m");
}

char *join_path(char *dir, char *filename, music_table_t *ht)
{
    char *fullpath;

    if (*dir != '\0')
    {
        fullpath = malloc(strlen(dir) + strlen(filename) + 2);
        if (fullpath == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for fullpath\n");
            free_ht(ht);
            free(dir);
            return (NULL);
        }
        sprintf(fullpath, "%s/%s", dir, filename);
    }
    else
        fullpath = strdup(filename);

    return (fullpath);
}

void print_player(music_file_t *selected)
{
    print_author();
    printf("\n");
    printf("\033[32m");
    printf("Previous: %s\n", selected->sprev ? selected->sprev->filename : "Nothing lol");
    printf("  ____________________________\n"
    " /|............................|\n"
    "| |:                          :|\n"
    "| |:  %s\n"
    "| |:     ,-.   _____   ,-.    :|\n"
    "| |:    ( `)) [_____] ( `))   :|\n"
    "|v|:     `-`   ' ' '   `-`    :|\n"
    "|||:     ,______________.     :|\n"
    "|||...../::::o::::::o::::\\.....|\n"
    "|^|..../:::O::::::::::O:::\\....|\n"
    "|/`---/--------------------`---|\n"
    "`.___/ /====/ /=//=/ /====/____/\n"
    "     `--------------------'\n", selected->filename);
    printf("Next: %s\n", selected->snext ? selected->snext->filename : "Nothing lol");
    printf("\033[0m");
}

int main(int argc, char *argv[])
{
    music_table_t *ht;
    music_file_t *selected;
    int size;
    char *fullpath = NULL;
    playback_t ctx = {0};

    print_author();

    if (argc < 2)
        size = get_music_files("musics.txt", ".");
    else
        size = get_music_files("musics.txt", argv[1]);

    ht = create_ht(size);
    ht->directory = strdup(argv[1]);
    build_dll(ht);

    selected = select_music_file(ht);
    if (selected != NULL)
    {
        fullpath = join_path(argv[1], selected->filename, ht);

        clearscreen();
        int ch;
        print_player(selected);
        if (play(argv[1], selected, &ctx, ht) != 0)
            printf("Failed to play the selected file\n");

        free(fullpath);
    }

    free_ht(ht);

    return 0;
}

