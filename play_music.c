#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"
#include "term_player.h"
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

bool is_finished = false;

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

bool kbhit() 
{ 
    struct termios term; 
    tcgetattr(0, &term); 
 
    struct termios term2 = term; 
    term2.c_lflag &= ~ICANON; 
    tcsetattr(0, TCSANOW, &term2); 
 
    int byteswaiting; 
    ioctl(0, FIONREAD, &byteswaiting); 
 
    tcsetattr(0, TCSANOW, &term); 
 
    return byteswaiting > 0; 
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;
    if (pDecoder == NULL)
            return;
    ma_uint64 FRAMES_READ = -1;
    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, &FRAMES_READ);
    if (FRAMES_READ == 0)
        is_finished = true;
    (void)pInput;
}

int handleNextAndPrev(int direction, music_file_t *selected, playback_t *ctx, char *dir, music_table_t *ht)
{
    if (direction == 1)
    {
        music_file_t *next = selected->snext;
        if (next != NULL)
        {
            stop_playback(ctx);
            is_finished = false;
            clearscreen();
            print_player(next);
            play(dir, next, ctx, ht);
        }
        else
        {
            printf("Im full\n");
            return (-1);
        }
    }
    else if (direction == 0)
    {
        music_file_t *prev = selected->sprev;
        if (prev != NULL)
        {
            stop_playback(ctx);
            is_finished = false;
            clearscreen();
            print_player(prev);
            play(dir, prev, ctx, ht);
        }
        else
        {
            printf("Im full\n");
            return (-1);
        }
    }

    return (0);
}

void handleSelectMenu(bool select_menu, char *fullpath, char *dir, music_table_t *ht, playback_t *ctx)
{
    if (select_menu)
    {
        free(fullpath);

        music_file_t *selectedmenu = select_music_file(ht);
        if (selectedmenu != NULL)
        {
            ma_device_uninit(&ctx->device);
            ma_decoder_uninit(&ctx->decoder);
            fullpath = join_path(dir, selectedmenu->filename, ht);

            clearscreen();
            print_player(selectedmenu);
            if (play(dir, selectedmenu, ctx, ht) != 0)
                printf("Failed to play the selected file\n");
            free(fullpath);
        }
    }
}

void cmd_loop(music_file_t *selected, music_table_t *ht, playback_t *ctx, char *dir, bool *select_menu, int *direction)
{
    while (true)
    {
        if (is_finished)
        {
            printf("Finally\n");
            music_file_t *next = selected->snext;
            if (next != NULL)
            {
                is_finished = false;
                clearscreen();
                print_player(next);
                play(dir, next, ctx, ht);
            }
            else
            {
                printf("Im full\n");
                break;
            }
        }

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
                printf("Audio %s\n", ctx->is_paused ? "paused" : "resumed");
            }
        }
    }
}

int play(char *dir, music_file_t *selected, playback_t *ctx, music_table_t *ht)
{
    ma_device_config deviceConfig;
    ma_result result;
    char *fullpath = join_path(dir, selected->filename, ht);
    bool select_menu = false;
    int direction = -1;

    result = ma_decoder_init_file(fullpath, NULL, &ctx->decoder);
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

    disableCursor();
    printf("Playing from %s\n", ctx->device.playback.name);
    printf("\033[32m(n)ext (p)rev (l)ibrary (s)pacebar`pause` (s)earch (q)uit\n\033[0m");
    ctx->is_playing = true;
    ctx->is_paused = false;


    cmd_loop(selected, ht, ctx, dir, &select_menu, &direction);
    enableCursor();

    handleSelectMenu(select_menu, fullpath, dir, ht, ctx);
    handleNextAndPrev(direction, selected, ctx, dir, ht);


    ctx->is_playing = false;
    stop_playback(ctx);

    return 0;
}
