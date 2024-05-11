#include "audio.h"
#include "term_player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    if (argv[1] != NULL)
        ht->directory = strdup(argv[1]);
    build_dll(ht);

    selected = select_music_file(ht);
    if (selected != NULL)
    {
        printf("Getting here\n");
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

