#ifndef PIPE_H
#define PIPE_H

#include "entity.h"
#include <stdbool.h>

typedef struct 
{
    Entity *pipe1;
    Entity *pipe2;
    bool passed;
}Pipe;

Pipe* Pipe_createPipe(SDL_Renderer *renderer, const char* texPath1, const char* texPath2, int x, int gap);
Pipe* Pipe_createPipeRandomGap(SDL_Renderer *renderer, const char* tex1, const char* tex2, int x);

void Pipe_update(SDL_Renderer *renderer, Pipe*pipe, float dt);
void Pipe_reset(Pipe *pipe, int x);





#endif