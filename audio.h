#ifndef _AUDIO_H_
#define _AUDIO_H_
#include "miniaudio.h"
#include <stdbool.h>
#include "term_player.h"

/**
 * struct playback_t - Structto represent the playback.
 * @device: The device playback is currently playing on.
 * @decoder: The decoder of the device.
 * @is_playing: Boolean on whether the device is playing or not.
 * @is_paused: Boolean on whether the playback is paused.
 */
typedef struct playback_t
{
	ma_device device;
	ma_decoder decoder;
	bool is_playing;
	bool is_finished;
	bool is_paused;
} playback_t;

void stop_playback(playback_t *ctx);
int play(music_file_t *selected, playback_t *ctx,
		 music_table_t *ht);
void clearscreen(void);
void handle_select_menu(bool select_menu, char *fullpath,
						music_table_t *ht, playback_t *ctx);
int handle_next_and_prev(int direction, music_file_t *selected,
						 playback_t *ctx, music_table_t *ht);
void handle_auto_next(playback_t *ctx,
					  music_table_t *ht, music_file_t *selected, bool *is_finished);

#endif /* _AUDIO_H_ */
