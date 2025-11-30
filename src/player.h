#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

typedef struct 
{
    Entity *entity;
    float velocity;
    float gravity;
    float flapStrength;
    float angle;
}Player;

Player *Player_createPlayer(SDL_Renderer *renderer, float x, float y, const char *path);
void Player_Flap(Player *player);
void Player_update(SDL_Renderer *renderer, Player* player, float dt);




#endif