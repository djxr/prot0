#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


// DEFAULTS
#define DEF_DISPLAY_NUM		1
#define DEF_ORIG_TILE_SZ	9
#define DEF_TILE_SZ		27

// State Enums /*{{{*/
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
// Structures /*{{{*/
typedef struct atlas_t
{
	SDL_Texture	*tex;
	SDL_Rect	*img;
}atlas_t;
struct game_t
{
	enum game_state	state;
	enum game_state	prev_state;
	SDL_Rect	rect;
	bool		run;
	atlas_t		atl;
};
struct player_t
{
	enum player_state	state;
	SDL_Rect		rect;
	int			rep;
	int			orbs;
	atlas_t		atl;
};
struct ai_t
{
	enum ai_state state;
	SDL_Rect		rect;
};
struct tile_t
{
	enum tile_type type;
};
/*}}}*/
// Global Variables /*{{{*/

int DISPLAY_NUM = DEF_DISPLAY_NUM;
int ORIG_TILE_SZ= DEF_ORIG_TILE_SZ;
int TILE_SZ = DEF_TILE_SZ;
struct game_t	game = {.state = cutscene, .run = true};
struct player_t	player = {.state = still};

SDL_Window	*win;
SDL_Renderer	*rend;

/*}}}*/
// Function Declarations /*{{{*/
int handle_arguments(int argc, char *argv[]);

int init();
int tini();

int handle_events(SDL_Event *e);
int update();
int render();

atlas_t	bld_atlas(char *bitmap_filename, size_t len);
void	dstr_atlas(atlas_t *a);

int filltile(atlas_t *a, int img_index);
int stamptile(atlas_t *a, int img_index, SDL_Rect dest);

int tile();
/*}}}*/
int main(int argc, char *argv[])
{
	handle_arguments(argc, argv);
	init();

	// Loop Variables 
	Uint32		time;
	Uint32		last_update =	0;
	Uint32		last_render =	0;

	SDL_Event	event;

	game.atl = bld_atlas("floor_tiles.bmp", 5);


	while(game.run)
	{
		time = SDL_GetTicks();

		while(SDL_PollEvent(&event))
			handle_events(&event);
		// update /*{{{*/
		if(time > last_update + 8) 
		{
			update();
			last_update = time;
		}/*}}}*/
		// render /*{{{*/
		if(time > last_render + 16) 
		{
			render();
			last_render = time;
		}/*}}}*/
	}

	dstr_atlas(&game.atl);
	tini();
	return 0;
}
int handle_arguments(int argc, char *argv[]) /*{{{*/
{
	for(int i = 0; i < argc; i++)
	{
		if(!strncmp(argv[i], "-d", 3))
		{
			i++;
			DISPLAY_NUM = atoi(argv[i]);
		}
		if(!strncmp(argv[i], "-s", 3))
		{
			i++;
			TILE_SZ = atoi(argv[i]);
		}
	}
	return 0;
}
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
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

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
				switch(e->type)
				{
					case SDL_KEYDOWN:
						switch(e->key.keysym.sym)
						{
							case SDLK_m:
								game.prev_state = game.state;
								game.state = menu;
								break;
							case SDLK_e:
								game.state = overworld;
								break;
						}
						break;
				}
				break;
			case menu:
				switch(e->type)
				{
					case SDL_KEYDOWN:
						switch(e->key.keysym.sym)
						{
							case SDLK_m:
								game.state = game.prev_state;
								break;
							case SDLK_ESCAPE:
								game.run = false;
								break;
						}
						break;
				}

				break;
			case overworld:
				switch(e->type)
				{
					case SDL_KEYDOWN:
						switch(e->key.keysym.sym)
						{
							case SDLK_m:
								game.prev_state = game.state;
								game.state = menu;
								break;
							case SDLK_e:
								game.state = underworld;
								break;
						}
						break;
				}

				break;
			case underworld:
				switch(e->type)
				{
					case SDL_KEYDOWN:
						switch(e->key.keysym.sym)
						{
							case SDLK_1:
								game.state = cutscene;
								break;
							case SDLK_m:
								game.prev_state = game.state;
								game.state = menu;
								break;
							case SDLK_e:
								game.state = overworld;
								break;
						}
						break;
				}

				break;
		}
		switch(player.state)
		{
			case still:
				break;
			case mov_up:
				break;
			case mov_left:
				break;
			case mov_right:
				break;
			case mov_down:
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

	switch(game.state)
	{
		case cutscene:
			filltile(&game.atl, 0);
			break;
		case menu:
			filltile(&game.atl, 1);
			break;
		case overworld:
			filltile(&game.atl, 2);
			break;
		case underworld:
			filltile(&game.atl, 3);
			break;
	}
	stamptile(&game.atl, 0, (SDL_Rect){0, 0, TILE_SZ, TILE_SZ});
	SDL_RenderPresent(rend);

	return 0;
}/*}}}*/

atlas_t bld_atlas(char *bitmap, size_t len) /*{{{*/
{
	SDL_Texture	*texture;
	SDL_Rect	*images;

	SDL_Surface *surface = SDL_LoadBMP(bitmap);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255,255));
	texture = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	// Create Rect[]
	images = calloc(len, sizeof(SDL_Rect));
	for (unsigned int i = 0; i < len; i++)
	{
		images[i].x = i * ORIG_TILE_SZ;
		images[i].y = 0;
		images[i].w = ORIG_TILE_SZ;
		images[i].h = ORIG_TILE_SZ;
	}
	atlas_t atlas = {.tex = texture, .img = images};

	return atlas;
}/*}}}*/
void	dstr_atlas(atlas_t *a) /*{{{*/
{
	SDL_DestroyTexture(a->tex);
	free(a->img);
	a->img = NULL;
}/*}}}*/
int filltile(atlas_t *a, int img_index) /*{{{*/
{
	for(int i = 0; i < (game.rect.h / TILE_SZ); i++)
		for(int j = 0; j < (game.rect.w / TILE_SZ); j++)
		{
			SDL_Rect paintbrush = {.x = j * TILE_SZ, .y = i * TILE_SZ, .w = TILE_SZ, .h = TILE_SZ};
			SDL_RenderCopy(rend, a->tex, &a->img[img_index], &paintbrush);
		}
	return 0;
}/*}}}*/
int stamptile(atlas_t *a, int img_index, SDL_Rect dest) /*{{{*/
{
	SDL_RenderCopy(rend, a->tex, &a->img[img_index], &dest);
	return 0;
}/*}}}*/
