#include "audio.h"
#include "term_player.h"

/**
 * handle_next_and_prev - Handles the next and prev of the player.
 * @direction: Whether to go next or prev.
 * @selected: The currently playing music.
 * @ctx: The playback struct.
 * @ht: The hashtable.
 * Return:  (-1) is there is no next and prev and 0 on success.
 */
int handle_next_and_prev(int direction, music_file_t *selected,
						 playback_t *ctx, music_table_t *ht)
{
	if (direction == 1)
	{
		music_file_t *next = selected->snext;

		if (next != NULL)
		{
			stop_playback(ctx);
			ctx->is_finished = false;
			clearscreen();
			print_player(next);
			play(next, ctx, ht);
		}
		else
		{
			printf_colour(31, "There is no next exiting now...\n");
			return (-1);
		}
	}
	else if (direction == 0)
	{
		music_file_t *prev = selected->sprev;

		if (prev != NULL)
		{
			stop_playback(ctx);
			ctx->is_finished = false;
			clearscreen();
			print_player(prev);
			play(prev, ctx, ht);
		}
		else
		{
			printf_colour(31, "There is no prev exiting now...\n");
			return (-1);
		}
	}

	return (0);
}

/**
 * handle_select_menu - Handles when user wants to select a new
 * music while one is currently playing.
 * @select_menu: Whether the user presses 'l' or not.
 * @fullpath: The fullpath to the music.
 * @ht: The hashtable.
 * @ctx: The plaback context.
 */
void handle_select_menu(bool select_menu, char *fullpath,
						music_table_t *ht, playback_t *ctx)
{
	if (select_menu)
	{
		music_file_t *selected_menu;

		free(fullpath);
		selected_menu = select_music(ht);

		if (selected_menu != NULL)
		{
			ma_device_uninit(&ctx->device);
			ma_decoder_uninit(&ctx->decoder);
			fullpath = join_path(ht->directory, selected_menu->filename, ht);

			clearscreen();
			print_player(selected_menu);
			if (play(selected_menu, ctx, ht) != 0)
				printf("Failed to play the selected file\n");
			free(fullpath);
		}
	}
}

/**
 * handle_auto_next - Handles automatic next after the curr has
 *					finished playing.
 * @ctx: Te playback context.
 * @ht: The hashtable.
 * @selected: The currently selected one.
 * @is_finished: Boolean to check if audio finished playing.
 */
void handle_auto_next(playback_t *ctx,
					  music_table_t *ht, music_file_t *selected, bool *is_finished)
{
	if (ctx->is_finished)
	{
		music_file_t *next;

		printf("Finally\n");
		next = selected->snext;
		if (next != NULL)
		{
			ctx->is_finished = false;
			*is_finished = false;
			stop_playback(ctx);
			clearscreen();
			print_player(next);
			play(next, ctx, ht);
		}
		else
		{
			printf_colour(31, "There is no next exiting now...\n");
			return;
		}
	}
}
