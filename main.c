#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

static const int width = 800;
static const int height = 600;

int main(int argc, char **argv)
{

	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}

    SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
  	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Event event;

	bool Running = true;
	while(Running) {

		if(SDL_PollEvent(&event)) {

			if ( event.key.keysym.sym == SDLK_ESCAPE ) {

				Running = false;
			}
			if ( event.type == SDL_QUIT ) {

				Running = false;
			}

		}

  		SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0);
  		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);		

	}


    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


/*

void display_bmp(char *file_name)
{
	SDL_Surface *image;

	image = SDL_LoadBMP(file_name);
	if (image == NULL) {
		fprintf(stderr, "Couldn’t load %s: %s\n", file_name, SDL_GetError());
		return;
	}

	if(SDL_BlitSurface(image, NULL, screen, NULL) < 0)
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	SDL_UpdateRect(screen, 0, 0, image->w, image->h);

	SDL_FreeSurface(image);
}

*/