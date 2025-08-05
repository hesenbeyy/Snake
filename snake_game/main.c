#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define GRID_SIZE 20

int main() {
	printf("Hello Snake!\n");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	
	SDL_Rect line;
	line.w = 1;
	line.h = HEIGHT;

	for (int x = 0; x <= WIDTH; x += GRID_SIZE) {
		line.x = x;
		line.y = 0;
		SDL_FillRect(surface, &line, SDL_MapRGB(surface->format, 128, 128, 128));
	}

	line.h = 1;
	line.w = WIDTH;
	
	for (int y = 0; y <= HEIGHT; y += GRID_SIZE) {
		line.y = y;
		line.x = 0;
		SDL_FillRect(surface, &line, SDL_MapRGB(surface->format, 128, 128 ,128));
	}

	SDL_UpdateWindowSurface(window);

	SDL_Rect snake;
	snake.x = WIDTH / 2;
	snake.y = HEIGHT / 2;
	snake.h = GRID_SIZE + 1;
	snake.w = GRID_SIZE + 1;

	SDL_FillRect(surface, &snake, SDL_MapRGB(surface->format, 0, 128, 0));

	SDL_UpdateWindowSurface(window);

	
	SDL_Event e;	
	int running = 1;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					printf("Left\n");
					snake.x -= GRID_SIZE;
					break;
				case SDLK_RIGHT: 
					printf("Right\n");
					snake.x += GRID_SIZE;
					break;
				case SDLK_UP:
					printf("Up\n");
					snake.y -= GRID_SIZE;
					break;
				case SDLK_DOWN:
					printf("Down\n");
					snake.y += GRID_SIZE;
					break;
				default:
					printf("lmao how\n");
					break;
				}

				if (snake.x < 0) snake.x = 0;
				if (snake.x > WIDTH - GRID_SIZE) snake.x = WIDTH - GRID_SIZE;
				if (snake.y < 0) snake.y = 0;
				if (snake.y > HEIGHT - GRID_SIZE) snake.y = HEIGHT - GRID_SIZE;
			}
		}

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		line.w = 1;
		line.h = HEIGHT;

		for (int x = 0; x <= WIDTH; x += GRID_SIZE) {
			line.x = x;
			line.y = 0;
			SDL_FillRect(surface, &line, SDL_MapRGB(surface->format, 128, 128, 128));
		}

		line.h = 1;
		line.w = WIDTH;

		for (int y = 0; y <= HEIGHT; y += GRID_SIZE) {
			line.y = y;
			line.x = 0;
			SDL_FillRect(surface, &line, SDL_MapRGB(surface->format, 128, 128, 128));
		}

		SDL_FillRect(surface, &snake, SDL_MapRGB(surface->format, 0, 128, 0));

		SDL_UpdateWindowSurface(window);


	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}