#include "menu.h"
#include "stdbool.h"
#include "graphics.h"
#include "utils.h"
#include "game.h"
#include "player.h"

void Menu_screen(SDL_Renderer *renderer)
{
    SDL_Texture *bgTex = Graphics_getTextureFromPath(renderer, BG_PATH);
    SDL_Rect *bgRect = Utils_createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Texture *birdTex = Graphics_getTextureFromPath(renderer, BIRD_MENU_PATH);
    int w, h;
    SDL_QueryTexture(birdTex, NULL, NULL, &w, &h);
    SDL_Rect *birdRect = Utils_createRect(WINDOW_WIDTH / 2 - w / 2, 170, w, h);

    SDL_Texture *startTex = Graphics_getTextureFromPath(renderer, START_BUTTON_PATH);
    int w2, h2;
    SDL_QueryTexture(startTex, NULL, NULL, &w2, &h2);
    SDL_Rect *startRect = Utils_createRect(WINDOW_WIDTH / 2 - w2 / 2, h + birdRect->y + 80, w2, h2);

    bool run = true;

    SDL_Event e;

    while (run)
    {
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                run = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    int mx = e.button.x;
                    int my = e.button.y;

                    if (mx >= startRect->x && mx <= startRect->x + startRect->w &&
                        my >= startRect->y && my <= startRect->y + startRect->h)
                    {

                        Player *player;

                        Game_init(renderer, &player);

                        Game_loop(renderer, player);

                        return;
                    }
                }
                break;
            }
        }
        Graphics_clearScreen(renderer);

        Graphics_renderTexture(renderer, bgTex, bgRect);

        Graphics_ShowText(renderer, mainFont100, "Flappy Bird", WINDOW_WIDTH / 2, 100, (SDL_Color){255, 255, 0, 255});
        Graphics_ShowText(renderer, mainFont50, "LAKSHYA PACHKHEDE", 610, 580, (SDL_Color){255, 255, 255, 255});
        Graphics_renderTexture(renderer, startTex, startRect);

        Graphics_renderTexture(renderer, birdTex, birdRect);

        Graphics_presentScreen(renderer);
    }
}