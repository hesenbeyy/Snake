#ifndef FUNCS_H
#define FUNCS_H


#include "macros.h"
#include <SDL.h>

void drawGrid(SDL_Surface* surface, SDL_Rect line );
Node* insertNewHead(Node* head, SDL_Rect new_position);
Node* deleteTail(Node* head);


#endif