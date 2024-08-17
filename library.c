#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "library.h"

#define MAX_ROWS 20
#define MAX_COLUMNS 20

const int MAX_USED_POSITIONS = 25;
// Why 25? 1 Perry + 10 bombs + 8 tools + 3 relatives = 22.
// But Tute (the reviser) prefers multiples of 5.
const int Q_BOMBS = 10;
const int Q_TOOLS = 8;
const int Q_RELATIVES = 3;

const char EMPTY = '-';

const char PERRY_LETTER = 'P';
const int INITIAL_LIVES = 3;
const int INITIAL_ENERGY = 100;
const bool INITIAL_HIDDEN_STATUS = false;

const char BOMB_LETTER = 'B';
const bool BOMB_DEACTIVATED_INITIALLY = false;
const int BOMB_ENERGY = 10;

const int MAX_TIMER = 300;
const int MIN_TIMER = 50;

const int INITIAL_Q_MOVEMENTS = 0;
const int MOVES_PER_ROBOT = 10;
const int Q_INITIAL_ROBOTS = 0;
const int ROBOT_ENERGY = 5;
const char ROBOT_LETTER = 'R';

const char HAT_LETTER = 'S';	// Hat in Spanish is "Sombrero".
const char SWEET_LETTER = 'G';	// Sweet in Spanish is "Golosina".
const int SWEET_ENERGY = 20;

const char PHINEAS_LETTER = 'H';
const char FERB_LETTER = 'F';
const char CANDACE_LETTER = 'C';

const int NONE = -1;		// No tool/bomb to interact with.
const int RELATIVE_CONTACT = 1;	// The distance between Perry and a relative to
				// interact.
const int ROBOT_CONTACT = 2;	// The same but with robots.

const char INITIAL_DIRECTION_PHINEAS = 'D';
const char INITIAL_DIRECTION_FERB = 'A';
const char INITIAL_DIRECTION_CANDACE = 'W';

const char UP_LETTER = 'W';
const char LEFT_LETTER = 'A';
const char DOWN_LETTER = 'S';
const char RIGHT_LETTER = 'D';
const char HIDDEN_LETTER = 'Q';

const int PLAYING_STATUS = 0;
const int LOST_STATUS = -1;
const int WON_STATUS = 1;

bool is_position_used(position_t used_positions[MAX_USED_POSITIONS],
		      int *q_used_positions, position_t new_position)
{
	bool answer = false;
	int i = 0;
	while (!answer && i < *q_used_positions) {
		if (used_positions[i].row == new_position.row &&
		    used_positions[i].column == new_position.column) {
			answer = true;
		}
		i++;
	}
	return answer;
}

position_t generate_new_position(position_t
				 used_positions[MAX_USED_POSITIONS],
				 int *q_used_positions)
{
	position_t candidate = { rand() % MAX_ROWS, rand() % MAX_COLUMNS };
	while (is_position_used(used_positions, q_used_positions,
				candidate)) {
		candidate = (position_t) {
		rand() % MAX_ROWS, rand() % MAX_COLUMNS};
	}
	used_positions[*q_used_positions] = candidate;
	(*q_used_positions)++;
	return candidate;
}

void initialize_quantities(game_t *game)
{
	game->q_bombs = Q_BOMBS;
	game->q_tools = Q_TOOLS;
	game->q_relatives = Q_RELATIVES;
}

void initialize_perry(game_t *game,
		      position_t used_positions[MAX_USED_POSITIONS],
		      int *q_used_positions)
{
	game->perry.lives = INITIAL_LIVES;
	game->perry.energy = INITIAL_ENERGY;
	game->perry.hidden = INITIAL_HIDDEN_STATUS;
	game->perry.position =
	    generate_new_position(used_positions, q_used_positions);
}

void initialize_bombs(game_t *game,
		      position_t used_positions[MAX_USED_POSITIONS],
		      int *q_used_positions)
{
	for (int i = 0; i < game->q_bombs; i++) {
		game->bombs[i].position =
		    generate_new_position(used_positions,
					  q_used_positions);
		game->bombs[i].timer = rand() % MAX_TIMER + MIN_TIMER;
		game->bombs[i].deactivated = BOMB_DEACTIVATED_INITIALLY;
	}
}

void initialize_robots(game_t *game)
{
	game->q_movements = INITIAL_Q_MOVEMENTS;
	game->q_robots = Q_INITIAL_ROBOTS;
}

void initialize_tools(game_t *game,
		      position_t used_positions[MAX_USED_POSITIONS],
		      int *q_used_positions)
{
	for (int i = 0; i < game->q_tools; i++) {
		game->tools[i].position =
		    generate_new_position(used_positions,
					  q_used_positions);
		if (i < 3) {
			game->tools[i].type = HAT_LETTER;
		} else {
			game->tools[i].type = SWEET_LETTER;
		}
	}
}

void initialize_relative(game_t *game, int i,
			 position_t used_positions[MAX_USED_POSITIONS],
			 int *q_used_positions, char who,
			 char relative_initial_direction)
{
	game->relatives[i].position =
	    generate_new_position(used_positions, q_used_positions);
	game->relatives[i].who = who;
	game->relatives[i].direction = relative_initial_direction;
}

void initialize_relatives(game_t *game,
			  position_t used_positions[MAX_USED_POSITIONS],
			  int *q_used_positions)
{
	initialize_relative(game, 0, used_positions,
			    q_used_positions, PHINEAS_LETTER,
			    INITIAL_DIRECTION_PHINEAS);
	initialize_relative(game, 1, used_positions,
			    q_used_positions, FERB_LETTER,
			    INITIAL_DIRECTION_FERB);
	initialize_relative(game, 2, used_positions,
			    q_used_positions, CANDACE_LETTER,
			    INITIAL_DIRECTION_CANDACE);
}

void initialize_everything(game_t *game)
{
	initialize_quantities(game);
	position_t used_positions[MAX_USED_POSITIONS];
	int q_used_positions = 0;
	initialize_perry(game, used_positions, &q_used_positions);
	initialize_bombs(game, used_positions, &q_used_positions);
	initialize_robots(game);
	initialize_tools(game, used_positions, &q_used_positions);
	initialize_relatives(game, used_positions, &q_used_positions);
}

void move_perry(game_t *game, char action)
{
	if (action == UP_LETTER && game->perry.position.row > 0) {
		game->perry.position.row--;
	} else if (action == LEFT_LETTER
		   && game->perry.position.column > 0) {
		game->perry.position.column--;
	} else if (action == DOWN_LETTER
		   && game->perry.position.row < MAX_ROWS - 1) {
		game->perry.position.row++;
	} else if (action == RIGHT_LETTER
		   && game->perry.position.column < MAX_COLUMNS - 1) {
		game->perry.position.column++;
	} else if (action == HIDDEN_LETTER) {
		game->perry.hidden = !game->perry.hidden;
	}
}

void move_relatives(game_t *game)
{
	for (int i = 0; i < game->q_relatives; i++) {
		if (game->relatives[i].direction == UP_LETTER) {
			(game->relatives[i].position.row)--;
			if (game->relatives[i].position.row == 0) {
				game->relatives[i].direction = DOWN_LETTER;
			}
		} else if (game->relatives[i].direction == RIGHT_LETTER) {
			(game->relatives[i].position.column)++;
			if (game->relatives[i].position.column ==
			    MAX_COLUMNS - 1) {
				game->relatives[i].direction = LEFT_LETTER;
			}
		} else if (game->relatives[i].direction == DOWN_LETTER) {
			(game->relatives[i].position.row)++;
			if (game->relatives[i].position.row ==
			    MAX_ROWS - 1) {
				game->relatives[i].direction = UP_LETTER;
			}
		} else if (game->relatives[i].direction == LEFT_LETTER) {
			(game->relatives[i].position.column)--;
			if (game->relatives[i].position.column == 0) {
				game->relatives[i].direction =
				    RIGHT_LETTER;
			}
		}
	}
}

int manhattan_distance(position_t a, position_t b)
{
	return abs(a.row - b.row) + abs(a.column - b.column);
}

int tool_to_interact_with(game_t *game)
{
	int tool_to_interact_with = NONE;
	int i = NONE;
	do {
		i++;
		if (manhattan_distance(game->perry.position,
				       game->tools[i].position) == 0) {
			tool_to_interact_with = i;
		}
	} while (i < game->q_tools - 1 && tool_to_interact_with == NONE);

	return tool_to_interact_with;
}

void interact_with_tool(game_t *game, int i)
{
	if (game->tools[i].type == HAT_LETTER) {
		(game->perry.lives)++;
	} else if (game->tools[i].type == SWEET_LETTER) {
		game->perry.energy += SWEET_ENERGY;
	}

	(game->q_tools)--;
	for (int k = i; k < game->q_tools; k++) {
		game->tools[k] = game->tools[k + 1];
	}
}

int bomb_to_interact_with(game_t *game)
{
	int bomb_to_interact_with = NONE;
	if (game->perry.hidden == false && game->perry.energy >=
	    BOMB_ENERGY) {
		int i = NONE;
		do {
			i++;
			if (manhattan_distance(game->perry.position,
					       game->bombs[i].position) ==
			    0 && game->bombs[i].deactivated == false) {
				bomb_to_interact_with = i;
			}
		} while (i < game->q_bombs - 1 && bomb_to_interact_with ==
			 NONE);
	}

	return bomb_to_interact_with;
}

void interact_with_bomb(game_t *game, int i)
{
	game->bombs[i].deactivated = true;
	game->perry.energy -= BOMB_ENERGY;
}

void interact_with_relatives(game_t *game)
{
	for (int i = 0; i < game->q_relatives; i++) {
		if (manhattan_distance(game->perry.position,
				       game->relatives[i].position) <=
		    RELATIVE_CONTACT && game->perry.hidden == false) {
			(game->perry.lives)--;
		}
	}
}

void interact_with_robots(game_t *game)
{
	for (int i = 0; i < game->q_robots; i++) {
		if (manhattan_distance
		    (game->perry.position, game->robots[i])
		    <= ROBOT_CONTACT) {
			if (game->perry.hidden == true) {
				(game->perry.lives)--;
			} else {
				if (game->perry.energy >= ROBOT_ENERGY) {
					game->perry.energy -= ROBOT_ENERGY;
				} else {
					(game->perry.lives)--;
				}
				(game->q_robots)--;
				game->robots[i] =
				    game->robots[game->q_robots];
				if (game->q_robots > 0) {
					game->robots =
					    realloc(game->robots, (size_t)
						    game->q_robots
						    * sizeof(position_t));
				} else {
					free(game->robots);
				}
			}
		}
	}
}

void handle_interactions(game_t *game)
{
	if (tool_to_interact_with(game) != NONE) {
		interact_with_tool(game, tool_to_interact_with(game));
	} else if (bomb_to_interact_with(game) != NONE) {
		interact_with_bomb(game, bomb_to_interact_with(game));
	}
	interact_with_relatives(game);
	interact_with_robots(game);
}

void decrease_timers(game_t *game)
{
	for (int i = 0; i < game->q_bombs; i++) {
		if (game->bombs[i].deactivated == false) {
			(game->bombs[i].timer)--;
			if (game->bombs[i].timer <= 0) {
				(game->perry.lives)--;
				game->bombs[i].deactivated = true;
			}
		}
	}
}

void generate_used_positions(game_t game, position_t positions_used[],
			     int *q_positions_used)
{
	*q_positions_used = 0;

	positions_used[*q_positions_used] = game.perry.position;
	(*q_positions_used)++;
	for (int i = 0; i < game.q_relatives; i++) {
		positions_used[*q_positions_used] =
		    game.relatives[i].position;
		(*q_positions_used)++;
	}
	for (int i = 0; i < game.q_bombs; i++) {
		if (game.bombs[i].deactivated == false &&
		    game.bombs[i].timer > 0) {
			positions_used[*q_positions_used] =
			    game.bombs[i].position;
			(*q_positions_used)++;
		}
	}
	for (int i = 0; i < game.q_tools; i++) {
		positions_used[*q_positions_used] = game.tools[i].position;
		(*q_positions_used)++;
	}
	for (int i = 0; i < game.q_robots; i++) {
		positions_used[*q_positions_used] = game.robots[i];
		(*q_positions_used)++;
	}
}

void build_robot(game_t *game)
{
	position_t used_positions[MAX_USED_POSITIONS];
	int q_used_positions;
	generate_used_positions(*game, used_positions, &q_used_positions);

	(game->q_robots)++;
	if (game->q_robots > 1) {
		game->robots =
		    realloc(game->robots,
			    (size_t) game->q_robots * sizeof(position_t));
	} else {
		game->robots = malloc((size_t) game->q_robots *
				      sizeof(position_t));
	}
	do {
		game->robots[game->q_robots - 1] =
		    generate_new_position(used_positions,
					  &q_used_positions);
	} while (manhattan_distance(game->perry.position,
				    game->robots[game->q_robots - 1])
		 <= ROBOT_CONTACT);
}

bool has_consequences(game_t *game, char action)
{
	return (action != HIDDEN_LETTER) &&
	    ((action == UP_LETTER && game->perry.position.row > 0) ||
	     (action == LEFT_LETTER && game->perry.position.column > 0) ||
	     (action == DOWN_LETTER
	      && game->perry.position.row < MAX_ROWS - 1)
	     || (action == RIGHT_LETTER
		 && game->perry.position.column < MAX_COLUMNS - 1));
}

void update_game_elements(game_t *game, char action)
{
	move_perry(game, action);
	if (has_consequences(game, action)) {
		move_relatives(game);
		decrease_timers(game);
		game->q_movements++;
		if (game->q_movements % MOVES_PER_ROBOT == 0) {
			build_robot(game);
		}
	}
	handle_interactions(game);
}

void indicate_perry_horizontal_position(game_t game)
{
	printf("   ");
	for (int j = 0; j < MAX_COLUMNS; j++) {
		if (j == game.perry.position.column) {
			printf(" V ");
		} else {
			printf("   ");
		}
	}
	printf("\n");
}

void indicate_perry_vertical_position(game_t game, int i)
{
	if (i == game.perry.position.row) {
		printf(" > ");
	} else {
		printf("   ");
	}
}

char get_letter_for_position(game_t game, position_t position)
{
	char c = EMPTY;
	if (manhattan_distance(game.perry.position, position) == 0) {
		c = PERRY_LETTER;
	} else {
		int i = 0;
		while (i < game.q_relatives && c == EMPTY) {
			if (manhattan_distance
			    (game.relatives[i].position, position) == 0) {
				c = game.relatives[i].who;
			}
			i++;
		}
		if (c == EMPTY) {
			i = 0;
			while (i < game.q_bombs && c == EMPTY) {
				if (manhattan_distance
				    (game.bombs[i].position,
				     position) == 0
				    && game.bombs[i].deactivated ==
				    false) {
					c = BOMB_LETTER;
				}
				i++;
			}
			if (c == EMPTY) {
				i = 0;
				while (i < game.q_tools && c == EMPTY) {
					if (manhattan_distance
					    (game.tools[i].position,
					     position) == 0) {
						c = game.tools[i].type;
					}
					i++;
				}
				if (c == EMPTY) {
					i = 0;
					while (i < game.q_robots
					       && c == EMPTY) {
						if (manhattan_distance
						    (game.robots[i],
						     position) == 0) {
							c = ROBOT_LETTER;
						}
						i++;
					}
				}
			}
		}
	}

	return c;
}

void print_row(game_t game, int i)
{
	for (int j = 0; j < MAX_COLUMNS; j++) {
		position_t position = { i, j };
		char c = get_letter_for_position(game, position);
		printf(" %c ", c);
	}
}

void print_menu(game_t game, int i)
{
	if (i == 0) {
		printf(" 🫡  ¡Bienvenido a tu misión, Perry! 🫡");
	} else if (i == 2) {
		if (game.perry.lives == 1) {
			printf(" ❤️  %d vida ❤️",
			       game.perry.lives);
		} else {
			printf(" ❤️  %d vidas ❤️",
			       game.perry.lives);
		}
	} else if (i == 3) {
		printf(" ⚡ %d puntos de energía ⚡",
		       game.perry.energy);
	} else if (i == 4) {
		printf(" 🥸  ¿Estás camuflado? ");
		if (game.perry.hidden) {
			printf("Sí ✅");
		} else {
			printf("No ❌");
		}
	} else if (i == 6) {
		int bombas_activas = 0;
		for (int j = 0; j < game.q_bombs; j++) {
			if (game.bombs[j].deactivated == false) {
				bombas_activas++;
			}
		}
		if (game.q_bombs == 1) {
			printf(" 🧨 %d bomba activa 🧨",
			       bombas_activas);
		} else {
			printf(" 🧨 %d bombas activas 🧨",
			       bombas_activas);
		}
	} else if (i == 7) {
		int suma = 0;
		for (int j = 0; j < game.q_bombs; j++) {
			if (game.bombs[j].deactivated == false) {
				suma += game.bombs[j].timer;
			}
		}
		printf
		    (" 🕰️  Temporizador promedio de bombas activas: %d 🕰️",
		     suma / game.q_bombs);
	} else if (i == 9) {
		int suma = 0;
		for (int j = 0; j < game.q_tools; j++) {
			if (game.tools[j].type == HAT_LETTER) {
				suma++;
			}
		}
		if (suma == 1) {
			printf(" 🎩 %d sombrero restante 🎩", suma);
		} else {
			printf(" 🎩 %d sombreros restantes 🎩", suma);
		}
	} else if (i == 10) {
		int suma = 0;
		for (int j = 0; j < game.q_tools; j++) {
			if (game.tools[j].type == SWEET_LETTER) {
				suma++;
			}
		}
		if (suma == 1) {
			printf(" 🍬 %d golosina restante 🍬", suma);
		} else {
			printf(" 🍬 %d golosinas restantes 🍬", suma);
		}
	} else if (i == 12) {
		if (game.q_robots == 1) {
			printf(" 🤖 %d robot 'vivos' 🤖",
			       game.q_robots);
		} else {
			printf(" 🤖 %d robots 'vivos' 🤖",
			       game.q_robots);
		}
	} else if (i == 13) {
		if (game.q_movements == 1) {
			printf(" 🦾 %d movimiento realizado 🦾",
			       game.q_movements);
		} else {
			printf(" 🦾 %d movimientos realizados 🦾",
			       game.q_movements);
		}
	}
}

void print_map(game_t game)
{
	indicate_perry_horizontal_position(game);
	for (int i = 0; i < MAX_ROWS; i++) {
		indicate_perry_vertical_position(game, i);
		print_row(game, i);
		print_menu(game, i);
		printf("\n");
	}
}

int get_status(game_t game)
{
	int status = 0;
	int q_deactivated_bombs = 0;
	if (game.perry.lives == 0) {
		status = LOST_STATUS;
	} else {
		for (int i = 0; i < game.q_bombs; i++) {
			if (game.bombs[i].deactivated) {
				q_deactivated_bombs++;
			}
		}
		if (game.q_bombs == q_deactivated_bombs) {
			status = WON_STATUS;
		}
	}
	if (status != PLAYING_STATUS && game.q_robots > 0) {
		while (game.q_robots > 1) {
			(game.q_robots)--;
			game.robots = realloc(game.robots, (size_t)
					      game.q_robots *
					      sizeof(position_t));
		}
		free(game.robots);
	}
	return status;
}
