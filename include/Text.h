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
        };

        Text();
        virtual ~Text();

        void setColor( const int& type );
        bool loadText( string s, SDL_Renderer* gRenderer );
        void renderText( SDL_Renderer* gRenderer );

    private:
        int x_text, y_text;

        LTexture text;
        SDL_Color textColor;

        TTF_Font *gFont;

};

#endif // TEXT_H
