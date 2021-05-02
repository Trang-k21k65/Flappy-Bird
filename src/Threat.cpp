#include "Threat.h"

Threat::Threat()
{
    x_threat = SCREEN_WIDTH;
}

Threat::~Threat()
{
    threat.free();
}

void Threat::set_threat_height()
{
    x_threat = SCREEN_WIDTH;
    int height = rand() % 300;
    threat_height = height;
}

void Threat::renderThreat( SDL_Renderer *gRenderer )
{
    clipThreat.x = 0;
    clipThreat.y = threat_height;
    clipThreat.w = threat.getWidth();
    clipThreat.h = 640;

    x_threat -= 2;

    threat.render( gRenderer, x_threat, 0, &clipThreat);
}

SDL_Rect Threat::get_RectCol1()
{
    SDL_Rect rect;

    rect.x = x_threat + 2;
    rect.y = -3;
    rect.w = 50;
    rect.h = THREAT_HEIGHT - threat_height;

    return rect;
}

SDL_Rect Threat::get_RectCol2()
{
    SDL_Rect rect;

    rect.x = x_threat + 2;
    rect.y = BLANK + THREAT_HEIGHT - threat_height - 4;
    rect.w = 50;
    rect.h = 640 - rect.y;

    return rect;
}

SDL_Rect Threat::get_RectBlank()
{
    SDL_Rect rect;

    rect.x = x_threat + 52;
    rect.y = THREAT_HEIGHT - threat_height;
    rect.w = 10;
    rect.h = BLANK;

    return rect;
}
