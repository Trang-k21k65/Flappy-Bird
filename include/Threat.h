#ifndef THREAT_H
#define THREAT_H

#include "LTexture.h"

#define THREAT_HEIGHT 455
#define DISTANCE 135

class Threat
{
    public:
        Threat();
        virtual ~Threat();

        void set_threat_height();
        void renderThreat( SDL_Renderer *gRenderer );
        SDL_Rect get_RectCol1();
        SDL_Rect get_RectCol2();

        SDL_Rect clipThreat;
        LTexture threat;

        int x_threat;
        int threat_height;
};

#endif // THREAT_H
