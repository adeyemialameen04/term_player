#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "miniaudio.h"
#include <stdbool.h>
#include "term_player.h"
typedef struct playback_t
{
  ma_device device;
  ma_decoder decoder;
  bool is_playing;
  bool is_paused;
} playback_t;

void stop_playback(playback_t *ctx);
int play(char *filename, playback_t *ctx, music_table_t *ht);
void clearscreen(void);
void playback_loop(music_table_t *ht, playback_t *ctx, char *fullpath);

#endif /* _AUDIO_H_ */
