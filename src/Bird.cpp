#include "Bird.h"

Bird::Bird()
{
    y_val = 0;
    x_bird = 100;
    y_bird = SCREEN_HEIGHT / 2;
    die = false;
    jump = false;
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
                if( !die ) y_val = -15;
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

bool Bird::checkCollision()
{
    bool success = false;

    if( (x_bird + bird.getWidth() > x_threat) && (x_bird < x_threat + threat.getWidth()) )
    {
        if( (y_bird < 320 - threat_height) || (y_bird + bird.getHeight() > 430 - threat_height) )
            success = true;
    }

    else
    {

    }
    if( y_bird < 0 || y_bird + bird.getHeight() > 640)
            success = true;

    return success;
}

bool Bird::isJump()
{
    if ()
}
