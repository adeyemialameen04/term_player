#include "audio.h"
#include "term_player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    music_table_t *ht;
    music_file_t *selected;
    int size;
    int path;
    char *path_ptr = NULL;
    char *fullpath = NULL;
    size_t n = 0;
    ssize_t chars_read;
    playback_t ctx = {0};

    printf("Press (0) to read the music files, and (1) to read from another directory: ");
    scanf("%d", &path);
    while (getchar() != '\n')
        ;

    if (path == 0)
    {
        size = get_music_files("musics.txt", ".");
    }
    else if (path == 1)
    {
        printf("Enter directory path: ");
        chars_read = getline(&path_ptr, &n, stdin);
        if (chars_read > 0 && path_ptr[chars_read - 1] == '\n')
            path_ptr[chars_read - 1] = '\0';
        size = get_music_files("musics.txt", path_ptr);
    }
    else
    {
        printf("Wrong command dumbass\n");
        exit(EXIT_FAILURE);
    }

    ht = create_ht(size);
    ht->directory = strdup(path_ptr);
    build_dll(ht);

    selected = select_music_file(ht);
    if (selected != NULL)
    {
        if (path_ptr != NULL)
        {
            fullpath = malloc(strlen(path_ptr) + strlen(selected->filename) + 2); // Allocate enough memory for the full path
            if (fullpath == NULL)
            {
                fprintf(stderr, "Unable to allocate memory for fullpath\n");
                free_ht(ht);
                free(path_ptr); // Free the dynamically allocated path_ptr
                return 1;
            }
            sprintf(fullpath, "%s/%s", path_ptr, selected->filename);
        }
        else
        {
            fullpath = strdup(selected->filename);
        }

        if (play(fullpath, &ctx) == 0)
            printf("Playing: %s\n", fullpath);
        else
            printf("Failed to play the selected file\n");

        free(fullpath);
    }
    else
    {
        printf("No file selected\n");
    }

    free_ht(ht);
    if (path_ptr != NULL)
        free(path_ptr);

    return 0;
}
