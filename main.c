#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// STATE ENUMS /*{{{*/
enum game_state {
	cutscene,
	menu,
	overworld,
	underworld
};
enum player_state {
	stand,
	mov_up,
	mov_left,
	mov_right,
	mov_down
};
enum ai_state {
	offscreen,
	idle
};/*}}}*/
// STATE MACHINE STRUCTURES /*{{{*/
struct game_t {
	enum game_state state;
};
struct player_t {
	enum player_state state;
};
struct ai_t {
	enum ai_state state;
};/*}}}*/

init(){
	if(SDL_Init(SDL_INIT_VIDEO)){
		fprintf("SDL Init failed: %s\n",SDL_GetError());
	}
	SDL_Log("I initialized");
}

tini(){
	SDL_Quit();
	SDL_Log("I de-initialized");
}

int main(int argc, char *argv[]){

	init();

	tini();
	return 0;
}
