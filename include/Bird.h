#ifndef BIRD_H
#define BIRD_H

#include "LTexture.h"
#include "Threat.h"

class Bird : public Threat
{
    public:
        Bird();
        virtual ~Bird();

        void renderBird( SDL_Renderer *gRenderer );
        void handleEvents( SDL_Event event );
        void handleMoveBird();
        bool checkCollision();
        bool isJump();
        bool isDie() { return die; }

        LTexture bird;

    private:
        float x_bird, y_bird;
        float y_val;
        bool die, jump;

};

#endif // BIRD_H
