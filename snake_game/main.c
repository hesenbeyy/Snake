#include <stdio.h>
#include <SDL.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define GRID_SIZE 20
#define FPS 60
#define frameDelay (1000 / FPS)

typedef enum {
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT
} Direction;

int main() {
	Uint32 frameStart;
	int frameTime;
	Direction currentDir = DIR_UP;
	int randAppleX;
	int randAppleY;
	srand(time(NULL));

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
	

	SDL_Rect snake;
	snake.x = WIDTH / 2;
	snake.y = HEIGHT / 2;
	snake.h = GRID_SIZE + 1;
	snake.w = GRID_SIZE + 1;

	SDL_FillRect(surface, &snake, SDL_MapRGB(surface->format, 0, 128, 0));

	SDL_UpdateWindowSurface(window);

	SDL_Rect apple;
	apple.x = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
	apple.y = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;
	apple.h = GRID_SIZE + 1;
	apple.w = GRID_SIZE + 1;

	SDL_UpdateWindowSurface(window);
	SDL_Event e;	
	int running = 1;
	int snakeSpeed = 150;
	Uint32 lastMoveTime = 0;
	while (running) {
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					printf("Left arrow pressed\n");
					if (currentDir != DIR_RIGHT) currentDir = DIR_LEFT;
					break;
				case SDLK_RIGHT: 
					printf("Right arrow pressed\n");
					if (currentDir != DIR_LEFT) currentDir = DIR_RIGHT;
					break;
				case SDLK_UP:
					printf("Up arrow pressed\n");
					if (currentDir != DIR_DOWN) currentDir = DIR_UP;
					break;
				case SDLK_DOWN:
					printf("Down arrow pressed\n");
					if(currentDir != DIR_UP) currentDir = DIR_DOWN;
					break;
				default:
					printf("thats it youre going into retard crusher\n");
					break;
				}

	
			}
			
		}

		Uint32 currentTime = SDL_GetTicks();


		if (currentTime - lastMoveTime > snakeSpeed) {
			switch (currentDir) {
			case DIR_RIGHT:
				snake.x += GRID_SIZE;
				break;
			case DIR_LEFT:
				snake.x -= GRID_SIZE;
				break;
			case DIR_UP:
				snake.y -= GRID_SIZE;
				break;
			case DIR_DOWN:
				snake.y += GRID_SIZE;
				break;
			}

			lastMoveTime = currentTime;
		}

		if (snake.x < 0) {
			printf("Left Wall Collision\n");
			snake.x = 0;
		}
		if (snake.x > WIDTH - GRID_SIZE) {
			printf("Right Wall Collision\n");
			snake.x = WIDTH - GRID_SIZE;	
		}
		if (snake.y < 0) {
			printf("Top Wall Collision\n");
			snake.y = 0;
		}
		
		if (snake.y > HEIGHT - GRID_SIZE) {
			printf("Bottom Wall Collision\n");
			snake.y = HEIGHT - GRID_SIZE;
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

		if (snake.x == apple.x && snake.y == apple.y) {
			printf("Collision Detected\n");
			while (1) {
				randAppleX = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
				randAppleY = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;
				if (randAppleX != apple.x || randAppleY != apple.y) {
					printf("Exiting the loop\n");
					apple.x = randAppleX;
					apple.y = randAppleY;
					break;
				}
				printf("Same position again, restarting while loop\n");
			}
		}

		SDL_FillRect(surface, &snake, SDL_MapRGB(surface->format, 0, 255, 0));
		SDL_FillRect(surface, &apple, SDL_MapRGB(surface->format, 255, 0, 0));

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
