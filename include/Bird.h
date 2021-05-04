#ifndef BIRD_H
#define BIRD_H

#include "Threat.h"
#include <SDL_mixer.h>

class Bird
{
    public:
        Bird();
        ~Bird();

        void renderBird( SDL_Renderer* gRenderer );
        void setFrameClips( SDL_Renderer* gRenderer );
        void handleEvents( SDL_Event& event, Mix_Chunk* wing );
        void handleMoveBird();
        bool checkCollision( SDL_Rect rect1, SDL_Rect rect2 );
        SDL_Rect get_RectBird();

        void set_x_bird( int val );
        void set_y_bird( int val );
        int get_y_bird();

        bool pause_bird;

    private:
        LTexture bird;

        int speed_bird;
        int x_bird, y_bird;

        SDL_Rect frameClips[frame];
        int current_frame;

};

#endif // BIRD_H
