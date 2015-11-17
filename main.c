#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// STATE ENUMS
enum game_state {
	cutscene,
	menu,
	overworld,
	underworld
		//...
};
enum player_state {
	stand,
	mov_up,
	mov_left,
	mov_right,
	mov_down
		//...
};
enum ai_state {
	offscreen,
	idle
		//...
};

// STATE MACHINE STRUCTURES
struct game_t {
	game_state .state;
	//...
}game;

struct player_t {
	player_state .state;
	//...
}player;

struct ai_t {
	ai_state .state;
	//...
}monster;

