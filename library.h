#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <stdbool.h>

#define MAX_Q_BOMBS 20
#define MAX_Q_TOOLS 100
#define MAX_Q_RELATIVES 10

typedef struct position {
	int row;
	int column;
} position_t;

typedef struct perry {
	int lives;
	int energy;
	bool hidden;
	position_t position;
} perry_t;

typedef struct bomb {
	position_t position;
	int timer;
	bool deactivated;
} bomb_t;

typedef struct tool {
	position_t position;
	char type;
} tool_t;

typedef struct relative {
	position_t position;
	char direction;
	char who;
} relative_t;

typedef struct game {
	perry_t perry;
	bomb_t bombs[MAX_Q_BOMBS];
	int q_bombs;
	tool_t tools[MAX_Q_TOOLS];
	int q_tools;
	relative_t relatives[MAX_Q_RELATIVES];
	int q_relatives;
	int q_movements;
	position_t *robots;
	int q_robots;
} game_t;

void initialize_everything(game_t * game);

void update_game_elements(game_t * game, char action);

void print_map(game_t game);

// Returns...
// ... 1 if the game is won (all bombs deactivated)
// ... -1 if the game is lost (no lives left)
// ... 0 if the game is still ongoing
// In case of winning or losing, this function will free the memory allocated
// throughout the game.
int get_status(game_t game);

#endif				/* __LIBRARY_H__ */
