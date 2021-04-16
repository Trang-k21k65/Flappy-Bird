#include "Threat.h"

Threat::Threat()
{
    x_threat = 0;
}

Threat::~Threat()
{
    threat.free();
}

void Threat::set_threat_height()
{
    float height = rand() % 200;
    threat_height = height;
}

void Threat::renderThreat( SDL_Renderer *gRenderer )
{
    clipThreat.x = 0;
    clipThreat.y = threat_height;
    clipThreat.w = threat.getWidth();
    clipThreat.h = 640;

    threat.render( gRenderer, x_threat, 0, &clipThreat);
}
