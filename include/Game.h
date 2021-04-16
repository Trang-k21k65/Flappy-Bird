#ifndef GAME_H
#define GAME_H

#include "LTexture.h"
#include "Bird.h"
#include "Threat.h"
#include "Text.h"
#include <cstdlib>
#include <ctime>

class Game
{
    public:
        Game();
        virtual ~Game();

        bool init();
        bool loadImage();
        void gameLoop();

    private:
        Bird gBird;
        Threat gThreat;
        Text gText;
        Text mark;

        LTexture gBackground;
        LTexture gGround;

        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
};

#endif // GAME_H
