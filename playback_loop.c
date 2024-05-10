#include "term_player.h"
#include "audio.h"
#include <unistd.h>

void playback_loop(music_table_t *ht, playback_t *ctx, char *fullpath) {
	int ch;
	bool paused = false;
	music_file_t *selected = NULL;

	while ((ch = getchar()) != 'q') {
		if (ch == 'm') {
			clearscreen();
			selected = select_music_file(ht);
			if (selected != NULL) {
				free(fullpath);
				char *new_path = NULL;
				if (ht->directory != NULL) {
					new_path = malloc(strlen(ht->directory) + strlen(selected->filename) + 2);
					if (new_path == NULL) {
						fprintf(stderr, "Unable to allocate memory for fullpath\n");
						return;
					}
					sprintf(new_path, "%s/%s", ht->directory, selected->filename);
				} else {
					new_path = strdup(selected->filename);
				}
				stop_playback(ctx);
				if (play(new_path, ctx, ht) != 0) {
					printf("Failed to play the selected file\n");
				}
				fullpath = new_path;
			}
		}
	}

	stop_playback(ctx);
}
