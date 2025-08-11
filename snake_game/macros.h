#ifndef MACROS_H
#define MACROS_H

#define WIDTH 800
#define HEIGHT 600
#define GRID_SIZE 20
#define FPS 60
#define frameDelay (1000 / FPS)
#define GAME_OVER_DELAY 3000
#define RECORDS_FILE "recs.bin"

typedef enum {
	DIR_UP,
	DIR_DOWN,
	DIR_RIGHT,
	DIR_LEFT
} Direction;

typedef struct Node {
	SDL_Rect snake_position;
	struct Node* next;
} Node;



#endif