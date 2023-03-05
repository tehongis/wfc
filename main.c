#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const int width = 800;
static const int height = 600;

SDL_Texture *tiletexture = NULL;

void blittile(SDL_Renderer *renderer,SDL_Renderer *tiletexture,int tileid,int x,int y) {
		SDL_Rect srcrect;
		int row=tileid%50;
		int column= tileid/50;
		srcrect.x = 16 * row;
		srcrect.y = 16 * column;
		srcrect.w = 16;
		srcrect.h = 16;

		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		dstrect.w = 16;
		dstrect.h = 16;

		SDL_RenderCopy(renderer,tiletexture, &srcrect, &dstrect);
}

int main(int argc, char **argv)
{

	srand(time(NULL));

	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}

    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
  	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);

//    SDL_Texture *tiletexture = NULL;
    tiletexture = NULL;	
    SDL_Surface *tilesurface = IMG_Load("gfx/colored-transparent_packed.png");
    if (tilesurface) {
        tiletexture = SDL_CreateTextureFromSurface(renderer, tilesurface);
        SDL_FreeSurface(tilesurface);
    } else {
		printf("ERROR: Failed to load tilesheet.\n");
		exit(-1);
	}

	int cursorblinktimer = 0;
	SDL_Rect cursrect;
	int cx = 0;
	int cy = 0;


	SDL_Event event;

	bool Running = true;
	while(Running) {

		while( SDL_PollEvent( &event ) ){
			switch( event.type ){
				case SDL_QUIT:
					Running = false;
					break;

				case SDL_KEYDOWN:
					switch ( event.key.keysym.sym ) {
						case SDLK_ESCAPE:
							Running = false;
							break;
						case SDLK_LEFT:
							cx = cx - 1;
							break;
						case SDLK_RIGHT:
							cx = cx + 1;
							break;
						case SDLK_UP:
							cy = cy - 1;
							break;
						case SDLK_DOWN:
							cy = cy + 1;
							break;
					}
			}
		}
		
  		SDL_SetRenderDrawColor(renderer, 30, 30, 40, 0);
  		SDL_RenderClear(renderer);

		cursorblinktimer = (cursorblinktimer + 1 ) & 127;

		if (cursorblinktimer < 64) {
			cursrect.x = cx*16;
			cursrect.y = cy*16;
			cursrect.w = 16;
			cursrect.h = 16;
			SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
			SDL_RenderFillRect(renderer, &cursrect);
		}

		int r = 0;
		for (int y = 0;y < 37; y++ ) {
			for (int x = 0;x < 50; x++ ) {
				blittile(renderer,tiletexture,r++,x*16,y*16);
			}
		}


		SDL_RenderPresent(renderer);

	}

	SDL_DestroyTexture(tiletexture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}