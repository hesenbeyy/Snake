#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

int main() {
	printf("Hello Snake!\n");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 50;
	rect.h = 100;

	// draw

	SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0x00, 0x00, 0xFF));	

	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}