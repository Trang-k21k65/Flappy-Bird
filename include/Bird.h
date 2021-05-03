#ifndef BIRD_H
#define BIRD_H

#include "Threat.h"
#include <SDL_mixer.h>

class Bird
{
    public:
        Bird();
        virtual ~Bird();

        void renderBird( SDL_Renderer* gRenderer );
        void setAnimated( SDL_Renderer* gRenderer );
        void handleEvents( SDL_Event& event, Mix_Chunk* wing );
        void handleMoveBird();
        bool checkCollision( SDL_Rect rect1, SDL_Rect rect2 );
        SDL_Rect get_RectBird();

        void set_x_bird( int val ) { x_bird = val; }
        void set_y_bird( int val ) { y_bird = val; }
        bool isDie() { return die; }

        LTexture bird;
        bool pause_bird;
        bool is_click_icon; // biến trả về false nếu tọa độ chuột không nằm trong play/pause icon

        LTexture bird_animated;
        SDL_Rect frameClips[frame];

    private:
        bool die;
        int speed_bird;
        int x_bird, y_bird;


};

#endif // BIRD_H
