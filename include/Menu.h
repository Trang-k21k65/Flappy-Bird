#ifndef MENU_H
#define MENU_H

#include "Text.h"
#include "SDL_mixer.h"

#define PLAY_HEIGHT 74
#define PLAY_WIDTH 154

class Menu: public LTexture
{
    public:
        Menu();
        virtual ~Menu();

        int showStart( SDL_Renderer* gRenderer , Mix_Chunk* tap);
        int showTapPlay( SDL_Renderer* gRenderer );
        void showGameOver( SDL_Renderer* gRenderer );


    private:
        LTexture get_ready, tap, logo;

        // backgroung cho man hinh start
        LTexture start, gameover;

        // bien chi rect chua tect option
        LTexture play_rect[option];

        // text trong man hinh start
        Text text_option[option];

        // vi tri cua play_rect
        SDL_Rect pos_option[option];

        // bien check toa do cua chuot co nam trong play_rect hay khong
        bool selected[option];

        // speed cho background
        int speed;

        // vi tri cua chuot trong man hinh start
        int x_mouse, y_mouse;

        // Mouse Events
        SDL_Event mouse_event;

};

#endif // MENU_H
