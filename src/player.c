#include "player.h"
#include "settings.h"
#include "graphics.h"

Player *Player_createPlayer(SDL_Renderer *renderer, float x, float y, const char *path)
{
    Player *player = (Player *)malloc(sizeof(Player));

    player->entity = Entity_createEntity(renderer, x, y, path);

    player->velocity = 0.0f;
    player->gravity = GRAVITY;
    player->flapStrength = FLAP_STRENGTH;

    player->angle = 0;

    return player;
}

void Player_Render(SDL_Renderer *renderer, Player *player)
{
    Graphics_renderTextureFAngle(renderer, player->entity->texture, &player->entity->rect, player->angle); 
}

void Player_Fall(Player *player, float dt)
{
    player->velocity += player->gravity * dt;

    if (player->velocity > MAX_FALL_SPEED)
    {
        player->velocity = MAX_FALL_SPEED;
    }

    player->entity->rect.y += player->velocity * dt;

    player->angle = (player->velocity / MAX_FALL_SPEED) * 90.0f;

    if (player->angle < -25)
        player->angle = -25;
    if (player->angle > 90)
        player->angle = 90;
}

void Player_Flap(Player *player)
{
    player->velocity = FLAP_STRENGTH;
}

void Player_update(SDL_Renderer *renderer, Player *player, float dt)
{
    Player_Fall(player, dt);
    Player_Render(renderer, player);
}


