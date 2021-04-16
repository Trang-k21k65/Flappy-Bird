#ifndef THREAT_H
#define THREAT_H

#include "LTexture.h"

class Threat
{
    public:
        Threat();
        virtual ~Threat();

        void set_x_threat( int pos ) { x_threat = pos; }
        void set_threat_height();
        void renderThreat( SDL_Renderer *gRenderer );

        SDL_Rect clipThreat;
        LTexture threat;

        float x_threat;
        float threat_height;
};

#endif // THREAT_H
