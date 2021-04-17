#ifndef THREAT_H
#define THREAT_H

#include "LTexture.h"


#define THREAT_HEIGHT 31
#define THREAT_WIDTH 40

class Threat
{
    public:
        Threat();
        virtual ~Threat();

        void set_x_threat( int pos ) { x_threat = pos; }
        void set_threat_height( int val );
        void renderThreat( SDL_Renderer *gRenderer );
        int get_threat_height() { return threat_height; }

        SDL_Rect clipThreat;
        LTexture threat;

        int x_threat;
        int threat_height;
};

#endif // THREAT_H
