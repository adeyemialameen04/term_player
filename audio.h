#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "miniaudio.h"
#include <stdbool.h>

typedef struct playback_t
{
  ma_device device;
  ma_decoder decoder;
  bool is_playing;
} playback_t;

void stop_playback(playback_t *ctx);
int play(const char *filename, playback_t *ctx);

#endif /* _AUDIO_H_ */
