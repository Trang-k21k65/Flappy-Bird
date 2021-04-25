#include "Bird.h"

Bird::Bird()
{
    speed = 0;

    x_bird = 100;
    y_bird = SCREEN_HEIGHT / 2;

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

void Bird::handleEvents( SDL_Event event )
{
    // mouse event
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die ) speed = -4;
        }
    }

    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die )  speed = 4;
        }
    }
    //keyboard event
    if( event.type == SDL_KEYDOWN)
    {
        if( event.key.keysym.sym == SDLK_UP )
        {
            if( !die ) speed = -4;
        }
    }

    if( event.type == SDL_KEYUP)
    {
        if( event.key.keysym.sym == SDLK_UP )
        {
            if( !die ) speed = 4;
        }
    }
}

void Bird::handleMoveBird()
{
    y_bird += speed;
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

    rect.x = x_bird + 23;
    rect.y = y_bird + 31;
    rect.w = 55;
    rect.h = 39;

    return rect;
}
