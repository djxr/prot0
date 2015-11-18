#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define DISPLAY_NUM 0
#define PIXEL_SCALE_UP 4

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
	still,
	mov_up,
	mov_left,
	mov_right,
	mov_down
};
enum ai_state
{
	offscreen,
	idle
};
enum tile_type
{
	ground,
	wall,
	door,
	chest,
	shop
};
/*}}}*/
// STRUCTURES /*{{{*/
struct game_t
{
	enum game_state	state;
	bool		run;
	SDL_Rect	rect;
};
struct player_t
{
	enum player_state	state;
	int			rep;
};
struct ai_t
{
	enum ai_state state;
};
struct tile_t
{
	enum tile_type type;
};
/*}}}*/
// GLOBAL VARIABLES /*{{{*/
struct game_t	game = {.state = cutscene, .run = true};
struct player_t	player = {.state = still};

SDL_Window	*win;
SDL_Renderer	*rend;
/*}}}*/

int init() /*{{{*/
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER)) /*{{{*/
	{
		fprintf(stderr, "SDL Init failed: %s\n",SDL_GetError());
		return 1;
	}/*}}}*/

	SDL_GetDisplayBounds(DISPLAY_NUM, &game.rect);

	win = SDL_CreateWindow("windows, yo.",
			game.rect.x, game.rect.y,
			game.rect.w, game.rect.h,
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

int handle_events(SDL_Event *e) /*{{{*/
{	
	if(e->type == SDL_QUIT)
		game.run = false;
	else
	{
		switch(game.state)
		{
			case cutscene:
				break;
			case menu:
				break;
			case overworld:
				break;
			case underworld:
				break;
		}
	}
	return 0;
}/*}}}*/
int update() /*{{{*/
{
	switch(game.state)
	{
		case cutscene:
			break;
		case menu:
			break;
		case overworld:
			break;
		case underworld:
			break;
	}
	return 0;
}/*}}}*/
int render() /*{{{*/
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

	return 0;
}/*}}}*/

int main(int argc, char *argv[])
{
	init();

	Uint32		time;
	Uint32		last_update =	0;
	Uint32		last_render =	0;

	SDL_Event	event;

	while(game.run)
	{
		time = SDL_GetTicks();

		while(SDL_PollEvent(&event))
			handle_events(&event);

		if(time > last_update + 8)
		{
			update();
			last_update = time;
		}

		if(time > last_render + 16)
		{
			render();
			last_render = time;
		}
	}

	tini();
	return 0;
}
