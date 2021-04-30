#ifndef GAME_H
#define GAME_H

#include "Threat.h"
#include "Menu.h"
#include "Bird.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        bool init();
        bool loadImage();
        bool loadMixer();
        void gameRender();
        bool isGameOver();

    private:
        Bird gBird;
        Threat gThreat[3];
        Text mark;
        Menu gMenu;

        LTexture get_ready;
        LTexture gBackground;

        Mix_Chunk* gMusic[5];
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
};

#endif // GAME_H
