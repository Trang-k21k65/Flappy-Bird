#include "Bird.h"

Bird::Bird()
{
    y_val = 0;

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
    if( event.type == SDL_KEYDOWN)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                if( !die ) y_val = -5;
                break;
            default:
                break;
        }
    }
    else if( event.type == SDL_KEYUP)
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
                if( !die ) y_val = 4;
                break;
            default:
                break;
        }
    }
}

void Bird::handleMoveBird()
{
    y_bird += y_val;
}

bool Bird::checkCollision( SDL_Rect rect1, SDL_Rect rect2 )
{
    //rect2 < rect1
    bool success = false;

    if( ( rect1.x < rect2.x + rect2.w ) && ( rect1.x + rect1.w > rect2.x ) &&
        ( rect1.y < rect2.y + rect2.h ) && ( rect1.y + rect1.h > rect2.y ) )
    {
        success = true;
    }

    return success;
}

