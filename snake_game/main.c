#include <stdio.h>
#include <SDL.h>
#include <time.h>
#include "macros.h"
#include "funcs.h"

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
	SDL_Rect line = { 0 };

	drawGrid(surface, line);

	SDL_Rect snake;
	Node* head = (Node*)malloc(sizeof(Node));
	
	snake.x = WIDTH / 2;
	snake.y = HEIGHT / 2;
	snake.h = GRID_SIZE + 1;
	snake.w = GRID_SIZE + 1;

	head->snake_position = snake;
	head->next = NULL;

	Node* temp = head;
	while (temp){
		SDL_FillRect(surface, &temp->snake_position, SDL_MapRGB(surface->format, 0, 128, 0));
		temp = temp->next;
	}

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
	int directionChanged = 0;
	while (running) {
		frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = 0;
			}
			else if (e.type == SDL_KEYDOWN && directionChanged == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					printf("Left arrow pressed\n");
					if (currentDir != DIR_RIGHT) {
						currentDir = DIR_LEFT;
						directionChanged = 1;
					}
					break;
				case SDLK_RIGHT: 
					printf("Right arrow pressed\n");
					if (currentDir != DIR_LEFT) {
						currentDir = DIR_RIGHT;
						directionChanged = 1;
					}
					break;
				case SDLK_UP:
					printf("Up arrow pressed\n");
					if (currentDir != DIR_DOWN) {
						currentDir = DIR_UP;
						directionChanged = 1;
					}
					break;
				case SDLK_DOWN:
					printf("Down arrow pressed\n");
					if (currentDir != DIR_UP) {
						currentDir = DIR_DOWN;
						directionChanged = 1;
					}
					break;
				default:
					printf("thats it youre going into retard crusher\n");
					break;
				}

	
			}
			
		}

		Uint32 currentTime = SDL_GetTicks();
		
		SDL_Rect newHeadPosition = head->snake_position;


		if (currentTime - lastMoveTime > snakeSpeed) {
			switch (currentDir) {
			case DIR_RIGHT:
				newHeadPosition.x += GRID_SIZE;
				break;
			case DIR_LEFT:
				newHeadPosition.x -= GRID_SIZE;
				break;
			case DIR_UP:
				newHeadPosition.y -= GRID_SIZE;
				break;
			case DIR_DOWN:
				newHeadPosition.y += GRID_SIZE;
				break;
			}

			head = insertNewHead(head, newHeadPosition);
			directionChanged = 0;

			if (head->snake_position.x < 0) {
				printf("Left Wall Collision, Game lost!\n");
				SDL_Delay(GAME_OVER_DELAY);
				running = 0;
				break;
			}
			if (head->snake_position.x > WIDTH - GRID_SIZE) {
				printf("Right Wall Collision, Game lost!\n");
				SDL_Delay(GAME_OVER_DELAY);
				running = 0;
				break;
			}
			if (head->snake_position.y < 0) {
				printf("Top Wall Collision, Game lost!\n");
				SDL_Delay(GAME_OVER_DELAY);
				running = 0;
				break;
			}

			if (head->snake_position.y > HEIGHT - GRID_SIZE) {
				printf("Bottom Wall Collision, Game lost!\n");
				SDL_Delay(GAME_OVER_DELAY);
				running = 0;
				break;
			}

			Node* check = head->next;
			while (check) {
				if (check->snake_position.x == head->snake_position.x &&
					check->snake_position.y == head->snake_position.y) {
					printf("Self collision detected, Game lost!\n");
					SDL_Delay(GAME_OVER_DELAY);
					running = 0;
					break;
				}
				check = check->next;
			}


			if (!(head->snake_position.x == apple.x && head->snake_position.y == apple.y)) head = deleteTail(head);
			else {
				printf("Apple eaten\n");
				while (1) {
					randAppleX = (rand() % (WIDTH / GRID_SIZE)) * GRID_SIZE;
					randAppleY = (rand() % (HEIGHT / GRID_SIZE)) * GRID_SIZE;
					SDL_Rect check = { randAppleX, randAppleY, GRID_SIZE, GRID_SIZE };

					Node* temp = head;
					int valid = 1;
					while (temp) {
						if (check.x == temp->snake_position.x && check.y == temp->snake_position.y) {
							valid = 0;
							break;
						}
						temp = temp->next;
					}

					if (valid) {
						apple.x = randAppleX;
						apple.y = randAppleY;
						break;
					}
				}

			}

			lastMoveTime = currentTime;

		}

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		drawGrid(surface, line);

		Node* temp = head;
		while (temp) {
			if (temp == head) {
				SDL_FillRect(surface, &temp->snake_position, SDL_MapRGB(surface->format, 0, 255, 0));
				temp = temp->next;
			}
			else {
				SDL_FillRect(surface, &temp->snake_position, SDL_MapRGB(surface->format, 0, 128, 0));
				temp = temp->next;
			}
		}
		SDL_FillRect(surface, &apple, SDL_MapRGB(surface->format, 255, 0, 0));

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		SDL_UpdateWindowSurface(window);
	}

	while (head) {
		Node* temp = head;
		head = head->next;
		free(temp);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
