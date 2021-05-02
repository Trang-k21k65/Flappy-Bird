#ifndef TEXT_H
#define TEXT_H

#include <SDL_ttf.h>
#include <iostream>
#include "LTexture.h"

using namespace std;

class Text
{
    public:
        enum textColor
        {
            WHITE_TEXT = 0,
            ORANGE_TEXT = 1,
            RED_TEXT = 2,
            GREEN_TEXT = 3,
            YELLOW_TEXT = 4,
            BLUE_TEXT = 5,
        };

        Text();
        virtual ~Text();

        void setColor( const int& type );
        bool loadText( string s, SDL_Renderer* gRenderer, int size );
        void renderText( SDL_Renderer* gRenderer, int x_text, int y_text );

    private:
        LTexture text;
        SDL_Color textColor;

        TTF_Font *gFont;

};

#endif // TEXT_H
