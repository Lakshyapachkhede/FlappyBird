#include "game.h"
#include "player.h"
#include "input.h"
#include <stdbool.h>
#include "graphics.h"
#include "utils.h"
#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>
#include "collision.h"
#include "audio.h"

Mix_Chunk *scoreSound = NULL;
Mix_Chunk *overSound = NULL;

void Game_init(SDL_Renderer *renderer, Player **player)
{
    scoreSound = Audio_LoadSound(SCORE_SOUND_PATH);
    overSound = Audio_LoadSound(OVER_SOUND_PATH);
    *player = Player_createPlayer(renderer, 100, 300, BIRD_PATH);
}

void Game_doGameOver(bool *gameOver)
{
    *gameOver = true;
    Audio_StopMusic();
    Audio_PlaySound(overSound);
}

void Game_checkGameOver(bool *gameOver, Player *player, Pipe *pipes[5])
{

    for (int i = 0; i < 5; i++)
    {
        if (Collision_CheckCollisionF_Offset(&player->entity->rect, &pipes[i]->pipe1->rect, 10.0f) ||
            Collision_CheckCollisionF_Offset(&player->entity->rect, &pipes[i]->pipe2->rect, 10.0f))
        {
            Game_doGameOver(gameOver);
            return;
        }
    }
    if ((player->entity->rect.y < 0) || (player->entity->rect.y + player->entity->rect.h > WINDOW_HEIGHT))
        Game_doGameOver(gameOver);
}



void Game_ManagePipes(SDL_Renderer *renderer, Pipe *pipes[5], Player *player, float dt, int *score)
{
    for (int i = 0; i < 5; i++)
    {

        Pipe_update(renderer, pipes[i], dt);

        if (!pipes[i]->passed && player->entity->rect.x > pipes[i]->pipe1->rect.x + pipes[i]->pipe1->rect.w)
        {
            pipes[i]->passed = true;
            (*score)++;
            Audio_PlaySound(scoreSound);
        }

        if (pipes[i]->pipe1->rect.x + pipes[i]->pipe1->rect.w < 0)
        {
            float maxX = 0;
            for (int j = 0; j < 5; j++)
            {
                if (pipes[j]->pipe1->rect.x > maxX)
                    maxX = pipes[j]->pipe1->rect.x;
            }

            float newX = maxX + PIPE_SPACING;
            Pipe_reset(pipes[i], newX);
        }
    }
}

void Game_ShowScore(SDL_Renderer *renderer, float dt, int score)
{
    char fpsText[5];
    char scoreText[5];
    int fps = (int)(1.0f / dt);

    SDL_itoa(fps, fpsText, 10);

    Graphics_ShowText(renderer, mainFont16, fpsText, 10, 10, (SDL_Color){255, 255, 255, 255});

    SDL_itoa(score, scoreText, 10);

    Graphics_ShowText(renderer, mainFont50, scoreText, WINDOW_WIDTH / 2, 100, (SDL_Color){255, 255, 0, 255});
}

void Game_gameScreen(SDL_Renderer *renderer, Player *player, SDL_Texture *bgTex, SDL_Rect *bgRect, Pipe *pipes[5], float dt, int *score, bool *gameOver)
{

    Graphics_clearScreen(renderer);

    Graphics_renderTexture(renderer, bgTex, bgRect);

    Game_ManagePipes(renderer, pipes, player, dt, score);
    Game_checkGameOver(gameOver, player, pipes);

    Player_update(renderer, player, dt);

    Game_ShowScore(renderer, dt, *score);
}

void Game_loop(SDL_Renderer *renderer, Player *player)
{
    bool run = true;
    SDL_Event e;

    Uint32 lastTime = SDL_GetTicks();

    SDL_Texture *bgTex = Graphics_getTextureFromPath(renderer, BG_PATH);
    SDL_Rect *bgRect = Utils_createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Pipe *pipes[5];

    // initial pipes
    for (int i = 0; i < 5; i++)
    {
        pipes[i] = Pipe_createPipeRandomGap(renderer, PIPE_PATH, PIPE_PATH, 1000 + i * 300);
        
    }
    

    int score = 0;

    bool gameOver = false;

    Mix_Music *bgm = Audio_LoadMusic(BGM_PATH);
    Audio_PlayBGM(bgm);
    Mix_VolumeMusic(100);

    bool reset = false;


    while (run)
    {

        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        Input_processEvent(&e, &run, player, &reset);

        if (!gameOver)
        {
            Game_gameScreen(renderer, player, bgTex, bgRect, pipes, dt, &score, &gameOver);
        }
        else if(reset)
        {
            Game_init(renderer, &player);
            reset = false;
            Game_loop(renderer, player);
            return;

        }
        else if(gameOver)
        {

            Graphics_ShowText(renderer, mainFont100, "Game Over!", WINDOW_WIDTH / 2, 200, (SDL_Color){255, 0, 0, 255});
            Graphics_ShowText(renderer, mainFont16, "Enter to Restart", WINDOW_WIDTH / 2, 250, (SDL_Color){255, 255, 255, 255});
        }
 
        Graphics_presentScreen(renderer);
    }
}
