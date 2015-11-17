#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// STATE ENUMS /*{{{*/
enum game_state
{
	cutscene,
	menu,
	overworld,
	underworld
};
enum player_state
{
	stand,
	mov_up,
	mov_left,
	mov_right,
	mov_down
};
enum ai_state
{
	offscreen,
	idle
};/*}}}*/
// STATE MACHINE STRUCTURES /*{{{*/
struct game_t
{
	enum game_state state;
};
struct player_t
{
	enum player_state state;
};
struct ai_t
{
	enum ai_state state;
};/*}}}*/

SDL_Window	*win;

int init() /*{{{*/
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS))
	{
		fprintf(stderr, "SDL Init failed: %s\n",SDL_GetError());
	}

	win = SDL_CreateWindow(
			"windows yo.",
			0, 0,
			640, 480,
			0);

	SDL_Log("I initialized");
	return 0;
}/*}}}*/
int tini() /*{{{*/
{
	SDL_DestroyWindow(win);
	SDL_Quit();

	SDL_Log("I de-initialized");
	return 0;
}/*}}}*/

int main(int argc, char *argv[])
{

	init();

	SDL_Delay(2000);

	tini();
	return 0;
}
