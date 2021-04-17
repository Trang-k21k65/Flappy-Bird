#ifndef BIRD_H
#define BIRD_H

#include "LTexture.h"
#include "Threat.h"
#include <iostream>

class Bird : Threat
{
    public:
        Bird();
        virtual ~Bird();

        void renderBird( SDL_Renderer *gRenderer );
        void handleEvents( SDL_Event event );
        void handleMoveBird();
        bool checkCollision( SDL_Rect rect1, SDL_Rect rect2 );
        bool isDie() { return die; }

        LTexture bird;
        bool die;

    private:
        int x_bird, y_bird;
        int y_val;

};

#endif // BIRD_H
