#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include "player.h"
#include "audio.h"

void Game_init(SDL_Renderer *renderer, Player **player);
void Game_loop(SDL_Renderer *renderer, Player *player);

extern Mix_Chunk *scoreSound;
extern Mix_Chunk *overSound;

#endif