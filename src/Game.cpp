#include "Game.h"

Game::Game()
{
    gWindow = NULL;
    gRenderer = NULL;

    for( int i = 0; i < 5; i++)
    {
        gMusic[i] = NULL;
    }
}

Game::~Game()
{
    //Free the sound
    for( int i = 0; i < 5; i++)
    {
        Mix_FreeChunk( gMusic[i] );
    }

    for( int i = 0; i < 5; i++)
    {
        gMusic[i] = NULL;
    }

    //Free loaded images
	gBackground.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadImage()
{
    bool success = true;

    // load background
    if( !gBackground.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	// load bird
	if( !gBird.bird.loadFromFile( "image/bird.png", gRenderer ) )
    {
        printf( "Failed to load bird texture!\n" );
		success = false;
    }

    // load threat
    if( !gThreat[0].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    if( !gThreat[1].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    if( !gThreat[2].threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    return success;
}

bool Game::loadMixer()
{
    bool success = true;

    //Load tap_to_play sound effect
	gMusic[0] = Mix_LoadWAV( "mixer/tap_to_play.wav" );
	if( gMusic[0] == NULL )
	{
		printf( "Failed to load tap_to_play sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load wing sound effect
	gMusic[1] = Mix_LoadWAV( "mixer/wing.wav" );
	if( gMusic[1] == NULL )
	{
		printf( "Failed to load wing sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load mark sound effect
	gMusic[2] = Mix_LoadWAV( "mixer/mark.wav" );
	if( gMusic[2] == NULL )
	{
		printf( "Failed to load mark sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load collision sound effect
	gMusic[3] = Mix_LoadWAV( "mixer/collision.wav" );
	if( gMusic[3] == NULL )
	{
		printf( "Failed to load collision sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load die sound effect
	gMusic[4] = Mix_LoadWAV( "mixer/die.wav" );
	if( gMusic[4] == NULL )
	{
		printf( "Failed to load die sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    return success;
}

bool Game::isGameOver()
{
    bool success = false;
    // check Collision
    /*

        if( gBird.die == true)
        {
            //GAMEOVER
        }*/

        // hien thi diem
        //if( isJump() ) mark_value++;
    return success;
}

void Game::gameRender()
{
    int x = 0;

    gThreat[0].set_threat_height();
    gThreat[1].set_threat_height();
    gThreat[2].set_threat_height();

    mark.setColor( Text::WHITE_TEXT );
    //int mark_val = 0;

    //Main loop flag
    bool quit = false;

    int start_menu = gMenu.showStart( gRenderer, gMusic[0] );
    if( start_menu == 1 )
    {
        quit = true;
    }
    else
    {
        int tap_play_menu = gMenu.showTapPlay( gRenderer );
        if( tap_play_menu == 1 )
        {
            quit = true;
        }
    }

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            gBird.handleEvents( e, gMusic[1] );
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        x -= 4;

        // render background
        gBackground.render( gRenderer, x, 0 );
        gBackground.render( gRenderer, SCREEN_WIDTH + x, 0 );

        if( -x == SCREEN_WIDTH ) x = 0;

        // render threat (cot)
        if( gThreat[0].x_threat >= 0 )
        {
            gThreat[1].x_threat = gThreat[0].x_threat + SCREEN_WIDTH/3;
            gThreat[2].x_threat = gThreat[1].x_threat + SCREEN_WIDTH/3;
        }
        else
        {
            gThreat[0] = gThreat[1];
            gThreat[1] = gThreat[2];
            gThreat[2].set_threat_height();
        }

        for( int i = 0; i < 3; i++ )
        {
            gThreat[i].renderThreat( gRenderer );
        }

        // render bird
        gBird.renderBird( gRenderer );
        gBird.handleMoveBird();

        // check Collision
        for( int i = 0; i < 3; i++ )
        {
            bool check1 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol1() );
            bool check2 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol2() );
            if( check1 || check2 )
            {
                quit = true;
                break;
            }
        }

        if( quit == true )
        {
            gMenu.showGameOver( gRenderer );
        }

        //mark.renderText( gRenderer );

        SDL_RenderPresent( gRenderer );
        SDL_Delay(15);
    }
}
