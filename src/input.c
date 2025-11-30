#include "input.h"

void Input_processEvent(SDL_Event *e, bool *run, Player *player, bool *reset)
{
    if (SDL_PollEvent(e))
    {
        switch (e->type)
        {
        case SDL_QUIT:
            *run = false;
            break;

        case SDL_KEYDOWN:
            if (e->key.keysym.sym == SDLK_UP)   // arrow up key
            {
                Player_Flap(player);
            }
            
            else if (e->key.keysym.sym == SDLK_RETURN)  
            {
                *reset = true;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (e->button.button == SDL_BUTTON_LEFT)  // left mouse click
            {
                Player_Flap(player);
            }
            break;

        default:
            break;
        }
    }
}
