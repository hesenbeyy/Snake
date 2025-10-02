#include <SDL.h>
#include "funcs.h"
#include "macros.h"

void drawGrid(SDL_Surface* surface, SDL_Rect line) {
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
}

Node* insertNewHead(Node* head, SDL_Rect new_position){
	Node* newNode = (Node *)malloc(sizeof(Node));
	newNode->snake_position = new_position;
	newNode->next = head;
	return newNode;
}
Node* deleteTail(Node* head) {
	if (!head || head->next == NULL) {
		free(head);
		return NULL;
	}

	Node* temp = head;
	while (temp->next->next) 	temp = temp->next;
	temp->next = NULL;
	return head;
}