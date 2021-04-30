#ifndef BIRD_H
#define BIRD_H

#include "LTexture.h"
#include "Threat.h"
#include <iostream>
#include <SDL_mixer.h>

class Bird
{
    public:
        Bird();
        virtual ~Bird();

        void renderBird( SDL_Renderer *gRenderer );
        void handleEvents( SDL_Event& event, Mix_Chunk* wing );
        void handleMoveBird();
        bool checkCollision( SDL_Rect rect1, SDL_Rect rect2 );
        SDL_Rect get_RectBird();

        LTexture bird;
        bool die;

    private:
        int x_bird, y_bird;
        int speed;

};

#endif // BIRD_H
