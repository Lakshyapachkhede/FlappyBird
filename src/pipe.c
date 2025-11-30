#include "pipe.h"
#include "utils.h"
#include <stdbool.h>
#include "graphics.h"

Pipe *Pipe_createPipe(SDL_Renderer *renderer, const char *texPath1, const char *texPath2, int x, int gap)
{
    Pipe *pipe = (Pipe *)malloc(sizeof(Pipe));

    pipe->pipe1 = Entity_createEntity(renderer, x, 0, texPath1);
    pipe->pipe2 = Entity_createEntity(renderer, x, 0, texPath2);

    int w, h;

    SDL_QueryTexture(pipe->pipe1->texture, NULL, NULL, &w, &h);

    pipe->pipe1->rect.w = w;
    pipe->pipe1->rect.h = h;

    SDL_QueryTexture(pipe->pipe2->texture, NULL, NULL, &w, &h);

    pipe->pipe2->rect.w = w;
    pipe->pipe2->rect.h = h;

    pipe->pipe1->rect.y = Utils_generateRandomNumber(PIPE_MIN_H, PIPE_MAX_H);
    pipe->pipe2->rect.y = pipe->pipe1->rect.y + gap;

    pipe->pipe1->rect.y = -(pipe->pipe1->rect.h - pipe->pipe1->rect.y);


    pipe->passed = false;

    return pipe;
}

Pipe *Pipe_createPipeRandomGap(SDL_Renderer *renderer, const char *tex1, const char *tex2, int x)
{
    int gap = Utils_generateRandomNumber(MIN_GAP, MAX_GAP);
    return Pipe_createPipe(renderer, tex1, tex2, x, gap);
}

void Pipe_move(Pipe *pipe, float dt)
{
    pipe->pipe1->rect.x -= PIPE_VEL * dt;
    pipe->pipe2->rect.x -= PIPE_VEL * dt;
}

void Pipe_render(SDL_Renderer *renderer, Pipe *pipe)
{

    Graphics_renderTextureFAngle(renderer, pipe->pipe1->texture, &pipe->pipe1->rect, 180.0f);
    Graphics_renderTextureF(renderer, pipe->pipe2->texture, &pipe->pipe2->rect);
}

void Pipe_update(SDL_Renderer *renderer, Pipe *pipe, float dt)
{
    Pipe_move(pipe, dt);
    Pipe_render(renderer, pipe);
}

void Pipe_reset(Pipe *pipe, int x)
{
    int gap = Utils_generateRandomNumber(MIN_GAP, MAX_GAP);

    pipe->pipe1->rect.y = Utils_generateRandomNumber(PIPE_MIN_H, PIPE_MAX_H);
    pipe->pipe2->rect.y = pipe->pipe1->rect.y + gap;

    pipe->pipe1->rect.y = -(pipe->pipe1->rect.h - pipe->pipe1->rect.y);

    pipe->pipe1->rect.x = x;
    pipe->pipe2->rect.x = x;

    pipe->passed = false;

}
