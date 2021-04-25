#ifndef GAME_H
#define GAME_H

#include "LTexture.h"
#include "Bird.h"
#include "Threat.h"
#include "Text.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        bool init();
        bool loadImage();
        void gameLoop();
        int menu();

    private:
        Bird gBird;
        Threat gThreat[3];
        Text gText, mark;

        LTexture gBackground;
        LTexture gGround;

        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
};

#endif // GAME_H
