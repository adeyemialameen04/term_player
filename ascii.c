#include "term_player.h"

void print_author(void)
{
	printf("\033[0;32m" // Set text color to green
	   "<!-- //////////////////////////////////////////////////////////////////////////////////////////////////////// -->\n"
	   "<!-- //		  _    _		 _									 _		 _							 _	   // -->\n"
	   "<!-- //		 / \\  | |		 / \\	_ __ ___   ___	___ _ __	  / \\	 __| | ___ _   _  ___ _ __ ___ (_)	  // -->\n"
	   "<!-- //		/ _ \\ | |_____ / _ \\ | '_ ` _ \\ / _ \\/ _ \\ '_ \\	 / _ \\ / _` |/ _ \\ | | |/ _ \\ '_ ` _ \\| |	 // -->\n"
	   "<!-- //    / ___ \\| |_____/ ___ \\| | | | | |	__/  __/ | | |	/ ___ \\ (_| |	__/ |_| |  __/ | | | | | |	  // -->\n"
	   "<!-- //   /_/	\\_\\_|    /_/	 \\_\\_| |_| |_|\\___|\\___|_| |_| /_/	 \\_\\__,_|\\___|\\__, |\\___|_| |_| |_|_|	  // -->\n"
	   "<!-- //																			|___/					   // -->\n"
	   "<!-- //////////////////////////////////////////////////////////////////////////////////////////////////////// -->\n"
	   "\033[0m"); // Reset text color
}

void print_player(music_file_t *selected)
{
	print_author();
	printf("\n");
	printf("\033[32m");
	printf("Previous: %s\n", selected->sprev ? selected->sprev->filename : "Nothing lol");
	printf("  ____________________________\n"
	" /|............................|\n"
	"| |:						   :|\n"
	"| |:  %s\n"
	"| |:	  ,-.	_____	,-.    :|\n"
	"| |:	 ( `)) [_____] ( `))   :|\n"
	"|v|:	  `-`	' ' '	`-`    :|\n"
	"|||:	  ,______________.	   :|\n"
	"|||...../::::o::::::o::::\\.....|\n"
	"|^|..../:::O::::::::::O:::\\....|\n"
	"|/`---/--------------------`---|\n"
	"`.___/ /====/ /=//=/ /====/____/\n"
	"	  `--------------------'\n", selected->filename);
	printf("Next: %s\n", selected->snext ? selected->snext->filename : "Nothing lol");
	printf("\033[0m");
}
