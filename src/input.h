#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "player.h"


void Input_processEvent(SDL_Event *e, bool *run, Player *player, bool *reset);





#endif