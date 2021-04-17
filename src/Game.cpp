#include "Game.h"

Game::Game()
{
    gWindow = NULL;
    gRenderer = NULL;
}

Game::~Game()
{
    //Free loaded images
	gBackground.free();
	gGround.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
	gRenderer = NULL;

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
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
			}
		}
	}

	return success;
}

bool Game::loadImage()
{
    bool success = true;

    if( !gBackground.loadFromFile( "image/background.png", gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gGround.loadFromFile( "image/ground.png", gRenderer ) )
	{
		printf( "Failed to load ground texture!\n" );
		success = false;
	}

	if( !gBird.bird.loadFromFile( "image/bird.png", gRenderer ) )
    {
        printf( "Failed to load bird texture!\n" );
		success = false;
    }

    if( !gThreat1.threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    if( !gThreat2.threat.loadFromFile( "image/pipe.png", gRenderer ) )
    {
        printf( "Failed to load threat texture!\n" );
		success = false;
    }

    return success;
}

void Game::gameLoop()
{
    srand ( time(NULL) );

    gThreat1.set_threat_height( 100 );
    gThreat2.set_threat_height( 400 );

    int x = 0;

    gText.setColor( 0 );
    gText.loadText( "Mark: " ,gRenderer );

    mark.setColor( 0 );

    //Main loop flag
    bool quit = false;

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
            gBird.handleEvents( e );
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        x -= 4;

        gBackground.render( gRenderer, x, 0 );
        gBackground.render( gRenderer, SCREEN_WIDTH + x, 0 );

        gGround.render( gRenderer, x, gBackground.getHeight() );
        gGround.render( gRenderer, SCREEN_WIDTH + x, gBackground.getHeight() );

        for( int i = 0; i < 2; i++ )
        {
            gThreat1.set_x_threat( x + 350*i );
            gThreat1.renderThreat( gRenderer );

            gThreat2.set_x_threat( x + 350*i + SCREEN_WIDTH );
            gThreat2.renderThreat( gRenderer );
        }

        gBird.renderBird( gRenderer );

        gText.renderText( gRenderer );

        if( -x == SCREEN_WIDTH ) x = 0;

        gBird.handleMoveBird();



        // hien thi diem
        //if( isJump() ) mark_value++;
        //mark.renderText( gRenderer );

        SDL_RenderPresent( gRenderer );
    }
}
