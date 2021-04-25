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
    int height = rand() % 400;
    threat_height = height;
}

void Threat::renderThreat( SDL_Renderer *gRenderer )
{
    clipThreat.x = 0;
    clipThreat.y = threat_height;
    clipThreat.w = threat.getWidth();
    clipThreat.h = 640;

    x_threat -= 5;

    threat.render( gRenderer, x_threat, 0, &clipThreat);
}

SDL_Rect Threat::get_RectCol1()
{
    SDL_Rect rect;

    rect.x = x_threat;
    rect.y = 0;
    rect.w = 52;
    rect.h = THREAT_HEIGHT - threat_height;

    return rect;
}

SDL_Rect Threat::get_RectCol2()
{
    SDL_Rect rect;

    rect.x = x_threat;
    rect.y = DISTANCE + THREAT_HEIGHT - threat_height;
    rect.w = 52;
    rect.h = 640 - rect.y;

    return rect;
}
