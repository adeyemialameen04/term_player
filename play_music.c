#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"
#include "term_player.h"
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

bool is_finished = false;

/**
 * stop_playback - Stops current playback.
 * @ctx: The playback struct.
 */
void stop_playback(playback_t *ctx)
{
	if (ctx->is_playing)
	{
		ma_device_stop(&ctx->device);
		ma_device_uninit(&ctx->device);
		ma_decoder_uninit(&ctx->decoder);
		ctx->decoder = (ma_decoder){0};
		ctx->device = (ma_device){0};
		ctx->is_playing = false;
	}
}

/**
 * data_callback - Would be called while frames are being read.
 * @pDevice: The device its playing from.
 * @pOutput: The output its playing to.
 * @pInput: The input its playing from.
 * @frameCount: The framecount.
 */
void data_callback(ma_device *pDevice, void *pOutput, const void *pInput,
				   ma_uint32 frameCount)
{
	ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;
	ma_uint64 FRAMES_READ = -1;

	if (pDecoder == NULL)
		return;

	ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, &FRAMES_READ);

	if (FRAMES_READ == 0)
		is_finished = true;
	(void)pInput;
}

void cmd_loop(music_file_t *selected, music_table_t *ht, playback_t *ctx,
			  bool *select_menu, int *direction)
{
	while (true)
	{
		ctx->is_finished = is_finished;
		handle_auto_next(ctx, ht, selected, &is_finished);

		if (kbhit())
		{
			char ch = getchar();

			if (ch == 'q')
				break;
			else if (ch == 'l')
			{
				*select_menu = true;
				break;
			}
			else if (ch == 'n')
			{
				*direction = 1;
				break;
			}
			else if (ch == 'p')
			{
				*direction = 0;
				break;
			}
			else if (ch == ' ')
			{
				if (ctx->is_paused)
				{
					if (ma_device_start(&ctx->device) != MA_SUCCESS)
						printf("Failed to resume audio\n");

					ctx->is_paused = false;
				}
				else
				{
					ma_device_stop(&ctx->device);
					ctx->is_paused = true;
				}
				printf_colour(32, "Audio %s\n", ctx->is_paused ? "paused" : "resumed");
			}
		}
	}
}

/**
 * play - Plays the music and handles the commands.
 * @selected: The currently selcted music.
 * @ctx: The playback context.
 * @ht: The hashtable.
 * Return: int.
 */
int play(music_file_t *selected, playback_t *ctx, music_table_t *ht)
{
	ma_device_config deviceConfig;
	ma_result result;
	char *fullpath = join_path(ht->directory, selected->filename, ht);
	bool select_menu = false;
	int direction = -1;

	result = ma_decoder_init_file(fullpath, NULL, &ctx->decoder);
	if (result != MA_SUCCESS)
	{
		return (-2);
	}

	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = ctx->decoder.outputFormat;
	deviceConfig.playback.channels = ctx->decoder.outputChannels;
	deviceConfig.sampleRate = ctx->decoder.outputSampleRate;
	deviceConfig.dataCallback = data_callback;
	deviceConfig.pUserData = &ctx->decoder;

	if (ma_device_init(NULL, &deviceConfig, &ctx->device) != MA_SUCCESS)
	{
		printf("Failed to open playback device.\n");
		ma_decoder_uninit(&ctx->decoder);
		return (-3);
	}

	if (ma_device_start(&ctx->device) != MA_SUCCESS)
	{
		printf("Failed to start playback device.\n");
		ma_device_uninit(&ctx->device);
		ma_decoder_uninit(&ctx->decoder);
		return (-4);
	}

	disableCursor();
	printf("Playing from %s\n", ctx->device.playback.name);
	printf_colour(32, "(n)ext (p)rev (l)ibrary (s)pacebar`pause` (s)earch (q)uit\n");
	ctx->is_playing = true;
	ctx->is_paused = false;

	cmd_loop(selected, ht, ctx, &select_menu, &direction);
	enableCursor();

	handle_select_menu(select_menu, fullpath, ht, ctx);
	handle_next_and_prev(direction, selected, ctx, ht);

	ctx->is_playing = false;
	stop_playback(ctx);

	return (0);
}
