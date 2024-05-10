#include "term_player.h"
#include <stdbool.h>
#define MINIAUDIO_IMPLEMENTATION
#include <stdio.h>
#include "audio.h"

void stop_playback(playback_t *ctx)
{
        if (ctx->is_playing)
        {
                ma_device_stop(&ctx->device);
                ma_device_uninit(&ctx->device);
                ma_decoder_uninit(&ctx->decoder);
                ctx->is_playing = false;
        }
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
        /* playback_t *ctx = (playback_t *)pDevice->pUserData; */
        /* if (ctx->decoder.pUserData == NULL) */
        ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;
        if (pDecoder == NULL)
        {
                return;
        }

        ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

        (void)pInput;
}

static ma_uint64 g_PlaybackPosition = 0;

// Modify the function signature to include a boolean flag for pausing
int play(const char *filename, playback_t *ctx, music_table_t *ht)
{
    ma_device_config deviceConfig;
    ma_result result = ma_decoder_init_file(filename, NULL, &ctx->decoder);
    if (result != MA_SUCCESS)
    {
        return -2;
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
        return -3;
    }

    if (ma_device_start(&ctx->device) != MA_SUCCESS)
    {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&ctx->device);
        ma_decoder_uninit(&ctx->decoder);
        return -4;
    }

    printf("Press 's' to stop playback, 'm' to pause/resume...\n");
    ctx->is_playing = true;
    ctx->is_paused = false;

    int ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == 's')
        {
            break;
        }
        else if (ch == 'p') // Toggle pause/resume when 'm' key is pressed
        {
            if (ctx->is_paused)
            {
                if (ma_device_start(&ctx->device) != MA_SUCCESS)
                    printf("Failed to resume audio\n");

                ctx->is_paused = false;
                printf("Audio resumed\n");
            }
            else
            {
                ma_device_stop(&ctx->device);
                ctx->is_paused = true;
                printf("Audio paused\n");
            }
        }
    }

    ma_device_uninit(&ctx->device);
    ma_decoder_uninit(&ctx->decoder);
    return 0;
}