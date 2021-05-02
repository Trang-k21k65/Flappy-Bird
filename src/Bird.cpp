#include "Bird.h"

Bird::Bird()
{
    speed = 0;

    x_bird = 100;
    y_bird = 100;

    die = false;
}

Bird::~Bird()
{
    bird.free();
}

void Bird::renderBird( SDL_Renderer *gRenderer )
{
    bird.render( gRenderer, x_bird, y_bird );

}

void Bird::handleEvents( SDL_Event& event, Mix_Chunk* wing )
{
    // mouse event
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die )
            {
                speed = -4;
                Mix_PlayChannel( -1, wing, 0);
            }
        }
    }

    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die ) speed = 4;
        }
    }
}

void Bird::handleMoveBird()
{
    y_bird += speed;

    if( y_bird + 37 < 0 || y_bird + 61 > 640 )
    {
        die = true;
    }
}

bool Bird::checkCollision( SDL_Rect rect1, SDL_Rect rect2 )
{
    bool success = false;

    if( ( rect1.x < rect2.x + rect2.w ) && ( rect1.x + rect1.w > rect2.x ) &&
        ( rect1.y < rect2.y + rect2.h ) && ( rect1.y + rect1.h > rect2.y ) )
    {
        success = true;
    }

    return success;
}

SDL_Rect Bird::get_RectBird()
{
    SDL_Rect rect;

    rect.x = x_bird + 28;
    rect.y = y_bird + 30;
    rect.w = 40;
    rect.h = 34;

    return rect;
}

