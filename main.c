#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "library.h"

const char UP = 'W';
const char LEFT = 'A';
const char DOWN = 'S';
const char RIGHT = 'D';
const char HIDE = 'Q';

const int PLAYING = 0;
const int LOST = -1;
const int WON = 1;

void print_everything(game_t game, bool valid_action)
{
	printf("\n"); // For `system("clear")` to work.
	system("clear");
	print_map(game);
	if (valid_action){
		printf("\n    ➡️  Próximo movimiento: ");
	} else {
		printf("    ⚠️  Alguna de las acciones anteriores fue ");
		printf("inválida.\n    ➡️  Próximo movimiento: ");
	}
}

bool is_action_valid(char action)
{
	action = (char) toupper(action);
	return action == UP || action == LEFT || action == DOWN ||
	       action == RIGHT || action == HIDE;
}

char get_valid_action(bool * valid_action)
{
	char action = (char) getc(stdin);
	while (action == '\n'){
		*valid_action = true;
		action = (char) getc(stdin);
	}
	while (is_action_valid(action) == false){
		*valid_action = false;
		action = (char) getc(stdin);
	}
	action = (char) toupper(action);
	return action;
}

void print_winner_perry()
{
	printf("\n         ⣼⡟⠁⠈⠉⠻⢶⣄⡀  ⢀⡀");
	printf("\n          ⣠⣦⣤⣀⡀");
	printf("\n        ⢰⣯⣥⣄⣀⣤⣄⣤⣽⣿⣶⣞⠛⣿⡄");
	printf("\n        ⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣷                  _________________");
	printf("\n       ⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⡆           |                 |");
	printf("\n⢠⣤⣤⣤⣶⣾⣿⣿⣿⣿⣿⡿⠟⠛⣻⣟⣭⣿⠿⠿⠿⡿⠟⣟⢿⣿⣿⠟           |    ¡Ganaste!    |");
	printf("\n      ⢨⣞⣿⡿⠉⠉⣳⡀⠻⣷⣿⣿  ⢠⠇ ⣿⡼⠟⠁           /_________________|");
	printf("\n      ⠈⠻⠿⢥⠤⠒⡟⠳⣀⠈⠛⠦⠴⠚⠁  ⢯             /");
	printf("\n    ⢀⣀⡠⠤⠤⠼⠦⣤⡇ ⠈⠳⣄⣀     ⢸");
	printf("\n  ⣴⣞⣉⡀ ⣀⣀⣀⣀  ⠠⠤⠤⠤⠉⠻⡆   ⢸⡀");
	printf("\n    ⠉⠉⠉⠁ ⠈⡟⠓⠲⠤⠤⠤⠤⠶⠚⠁    ⡇");
	printf("\n          ⢱             ⡇     ⢀⣀⣀⣀⣀⣀⡀");
	printf("\n          ⢸             ⡇ ⢀⡴⢾⡋⠉     ⠈⠉⠓⠦⢄⡀");
	printf("\n          ⢸⡄           ⠈⠳⣴⠋ ⣀⡹⠶⡖⠊⠉⠉⠉⠉⠉⠉⠉⢉⣿");
	printf("\n          ⢸⡇             ⠈⠳⣍   ⠘⢦⡀    ⢀⡼⠋⠁");
	printf("\n         ⣠⠏                ⠘⢦⡀⢀⣀⡀⠽⢦⠤⣠⠔⠉");
	printf("\n        ⢰⠃ ⡇            ⢸⡗⠦⣄ ⠱⡄   ⡼⠋⠁");
	printf("\n   ⣠⣤⣴⣶⣤⠏⢀⠞⡇            ⢸⡇ ⠈⠳⣄⠘⣆⣤⢿⡶");
	printf("\n  ⢀⣝⣻⣿⢿⡟⢠⠏ ⣇            ⢸⣷⡖⠒⢂⣈⣿⡿⢿⣯⣤⣄⣀");
	printf("\n  ⠛⠛⠻⣿ ⣩⠏  ⢻            ⢸⡇⢹⡿⣿⡿⠳⢶⣤⣿⣝⠛⠚⠃");
	printf("\n    ⢀⣼⣰⠋   ⢸            ⢸⡇ ⣻⠎   ⠈⢹⣿⡇");
	printf("\n    ⠘⢿⠃  ⢀⡴⠋            ⠘⢧⡴⠉      ⠉");
	printf("\n        ⣠⠋                ⠙⢦⡀");
	printf("\n       ⣼⠁                   ⠱⡄");
	printf("\n       ⢿    ⣤⣤⠤⠤⠤⠤⠤⠤⠤⣤⣄⣀     ⣹");
	printf("\n        ⠳⡀ ⠸⡅          ⠈⢹⡆  ⢠⠇");
	printf("\n    ⢀⣀⠤⠤⠒⠛⢦⣤⢧⡄          ⣸⡇⢀⣴⣋");
	printf("\n   ⠞⠯⣄⣀  ⢀⡠⠔⠚⠁         ⣎⣉⠙⠋⠉⠉⠉⠓⠢⣤⡄");
	printf("\n     ⠈⡉⠓⠒⠉              ⠉⠙⠲⢤⣤⠤⠔⠊⠉⠁\n");
}

void show_loser_perry()
{
	printf("\n         ⣼⡟⠁⠈⠉⠻⢶⣄⡀  ⢀⡀");
	printf("\n          ⣠⣦⣤⣀⡀");
	printf("\n        ⢰⣯⣥⣄⣀⣤⣄⣤⣽⣿⣶⣞⠛⣿⡄");
	printf("\n        ⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣷                  __________________");
	printf("\n       ⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢿⣿⣿⡆           |                  |");
	printf("\n⢠⣤⣤⣤⣶⣾⣿⣿⣿⣿⣿⡿⠟⠛⣻⣟⣭⣿⠿⠿⠿⡿⠟⣟⢿⣿⣿⠟           |    ¡Perdiste!    |");
	printf("\n      ⢨⣞⣿⡿⠉⠉⣳⡀⠻⣷⣿⣿  ⢠⠇ ⣿⡼⠟⠁           /__________________|");
	printf("\n      ⠈⠻⠿⢥⠤⠒⡟⠳⣀⠈⠛⠦⠴⠚⠁  ⢯             /");
	printf("\n    ⢀⣀⡠⠤⠤⠼⠦⣤⡇ ⠈⠳⣄⣀     ⢸");
	printf("\n  ⣴⣞⣉⡀ ⣀⣀⣀⣀  ⠠⠤⠤⠤⠉⠻⡆   ⢸⡀");
	printf("\n    ⠉⠉⠉⠁ ⠈⡟⠓⠲⠤⠤⠤⠤⠶⠚⠁    ⡇");
	printf("\n          ⢱             ⡇     ⢀⣀⣀⣀⣀⣀⡀");
	printf("\n          ⢸             ⡇ ⢀⡴⢾⡋⠉     ⠈⠉⠓⠦⢄⡀");
	printf("\n          ⢸⡄           ⠈⠳⣴⠋ ⣀⡹⠶⡖⠊⠉⠉⠉⠉⠉⠉⠉⢉⣿");
	printf("\n          ⢸⡇             ⠈⠳⣍   ⠘⢦⡀    ⢀⡼⠋⠁");
	printf("\n         ⣠⠏                ⠘⢦⡀⢀⣀⡀⠽⢦⠤⣠⠔⠉");
	printf("\n        ⢰⠃ ⡇            ⢸⡗⠦⣄ ⠱⡄   ⡼⠋⠁");
	printf("\n   ⣠⣤⣴⣶⣤⠏⢀⠞⡇            ⢸⡇ ⠈⠳⣄⠘⣆⣤⢿⡶");
	printf("\n  ⢀⣝⣻⣿⢿⡟⢠⠏ ⣇            ⢸⣷⡖⠒⢂⣈⣿⡿⢿⣯⣤⣄⣀");
	printf("\n  ⠛⠛⠻⣿ ⣩⠏  ⢻            ⢸⡇⢹⡿⣿⡿⠳⢶⣤⣿⣝⠛⠚⠃");
	printf("\n    ⢀⣼⣰⠋   ⢸            ⢸⡇ ⣻⠎   ⠈⢹⣿⡇");
	printf("\n    ⠘⢿⠃  ⢀⡴⠋            ⠘⢧⡴⠉      ⠉");
	printf("\n        ⣠⠋                ⠙⢦⡀");
	printf("\n       ⣼⠁                   ⠱⡄");
	printf("\n       ⢿    ⣤⣤⠤⠤⠤⠤⠤⠤⠤⣤⣄⣀     ⣹");
	printf("\n        ⠳⡀ ⠸⡅          ⠈⢹⡆  ⢠⠇");
	printf("\n    ⢀⣀⠤⠤⠒⠛⢦⣤⢧⡄          ⣸⡇⢀⣴⣋");
	printf("\n   ⠞⠯⣄⣀  ⢀⡠⠔⠚⠁         ⣎⣉⠙⠋⠉⠉⠉⠓⠢⣤⡄");
	printf("\n     ⠈⡉⠓⠒⠉              ⠉⠙⠲⢤⣤⠤⠔⠊⠉⠁\n");
}

int main() 
{
	srand((unsigned) time(NULL));
	game_t game;
	initialize_everything(&game);
	int status = get_status(game);
	bool action_valid = true;

	while (status == PLAYING) {
		print_everything(game, action_valid);
		update_game_elements(&game, get_valid_action(&action_valid));
		status = get_status(game);
	}

	printf("\n");
	system("clear");
	if (status == WON) {
		print_winner_perry();
	} else if (status == LOST) {
		show_loser_perry();
	}

	return 0;
}