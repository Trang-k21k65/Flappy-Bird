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

        void set_x_bird( int val ) { x_bird = val; }
        void set_y_bird( int val ) { y_bird = val; }
        bool isDie() { return die; }
        SDL_Rect get_RectBird();

        LTexture bird;
        int x_bird, y_bird;

    private:
        bool die;

        int speed;


};

#endif // BIRD_H
