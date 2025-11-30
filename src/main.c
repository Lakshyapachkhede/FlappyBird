#include "settings.h"
#include "graphics.h"
#include "audio.h"
#include "game.h"
#include "player.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;

    Graphics_initializeGraphics(&window, &renderer, GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Audio_InitialiseAudio();

    // Player *player;

    // Game_init(renderer, &player);

    // Game_loop(renderer, player);

    Menu_screen(renderer);


    
    Graphics_cleanupGraphics(window, renderer);
    Audio_CleanUpAudio();

    return 0;
}