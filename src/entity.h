#ifndef ENTITY_H
#define ENTITY_H

#include "SDL2/SDL.h"


typedef struct 
{
    SDL_FRect rect;
    SDL_Texture *texture;
}Entity;

Entity *Entity_createEntity(SDL_Renderer *renderer, float x, float y, const char* path);
void Entity_Render(SDL_Renderer *renderer, Entity *entity);




#endif