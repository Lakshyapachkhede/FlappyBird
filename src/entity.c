#include "entity.h"
#include "graphics.h"
#include <stdlib.h>

Entity *Entity_createEntity(SDL_Renderer *renderer, float x, float y, const char *path)
{
    Entity *entity = (Entity *)malloc(sizeof(Entity));

    entity->texture = Graphics_getTextureFromPath(renderer, path);

    entity->rect.x = x;
    entity->rect.y = y;

    int w, h;

    SDL_QueryTexture(entity->texture, NULL, NULL, &w, &h);

    entity->rect.w = w;
    entity->rect.h = h;

    return entity;
}
void Entity_Render(SDL_Renderer *renderer, Entity *entity)
{
    Graphics_renderTextureF(renderer, entity->texture, &entity->rect);
}