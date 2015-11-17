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
SDL_Renderer	*rend;

int init() /*{{{*/
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS))
	{
		fprintf(stderr, "SDL Init failed: %s\n",SDL_GetError());
		return 1;
	}

	win = SDL_CreateWindow(
			"windows yo.",
			0, 0,
			640, 480,
			0);
	if(win == NULL)
	{
		SDL_Log("Window creation failed: %s", SDL_GetError());
	}

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if(rend == NULL)
	{
		SDL_Log("Renderer creation failed: %s", SDL_GetError());
	}

	SDL_Log("I initialized");

	return 0;
}/*}}}*/
int tini() /*{{{*/
{
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();

	SDL_Log("dezilaitini I");
	return 0;
}/*}}}*/

int render()
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

	return 0;
}

int main(int argc, char *argv[])
{

	init();

	render();
	SDL_Delay(2000);

	tini();
	return 0;
}
