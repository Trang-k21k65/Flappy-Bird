#include "Menu.h"

Menu::Menu()
{
    speed = 0;

    x_mouse = 0;
    y_mouse = 0;

    selected[0] = false;
    selected[1] = false;
}

Menu::~Menu()
{
    start.free();
    gameover.free();

    logo.free();
    get_ready.free();
    tap.free();

    play_rect[0].free();
    play_rect[1].free();
}

int Menu::showStart( SDL_Renderer* gRenderer, Mix_Chunk* tap )
{
    // load background cho man hinh start
    if( !start.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background start texture!\n" );
		return 1;
	}

	// load logo
    if( !logo.loadFromFile( "image/logo.png", gRenderer ) )
	{
		printf( "Failed to load logo texture!\n" );
		return 1;
	}

    // load rect chua text option
    if( !play_rect[0].loadFromFile( "image/play_rect.png", gRenderer ) )
	{
		printf( "Failed to load play_rect texture!\n" );
		return 1;
	}

	if( !play_rect[1].loadFromFile( "image/play_rect.png", gRenderer ) )
	{
		printf( "Failed to load play_rect texture!\n" );
		return 1;
	}

    // Set rect chi play_rect
	pos_option[0].x = (SCREEN_WIDTH - PLAY_WIDTH) / 2;
	pos_option[0].y = 400;
	pos_option[0].h = PLAY_HEIGHT;
	pos_option[0].w = PLAY_WIDTH;

	pos_option[1].x = (SCREEN_WIDTH - PLAY_WIDTH) / 2;
	pos_option[1].y = 500;
	pos_option[1].h = PLAY_HEIGHT;
	pos_option[1].w = PLAY_WIDTH;

	// Set text trong man hinh start
	text_option[0].setColor( Text::ORANGE_TEXT );
	text_option[0].loadText( "Play", gRenderer );

	text_option[1].setColor( Text::ORANGE_TEXT );
	text_option[1].loadText( "Exit", gRenderer );

	while(true)
    {
        while( SDL_PollEvent( &mouse_event ) != 0 )
        {
            switch( mouse_event.type )
            {
                case SDL_QUIT:
                    return 1;
                    break;

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState( &x_mouse, &y_mouse );

                    for( int i = 0; i < option; i++ )
                    {
                        if( checkFocusMouse( x_mouse, y_mouse, pos_option[i] ) )
                        {
                            if( selected[i] == false )
                            {
                                selected[i] = true;
                                //text_option[i].setColor( Text::BLUE_TEXT );
                            }
                        }
                        else
                        {
                            if( selected[i] == true )
                            {
                                selected[i] = false;
                                //text_option[i].setColor( Text::ORANGE_TEXT );
                            }
                        }
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState( &x_mouse, &y_mouse );
                    Mix_PlayChannel( -1, tap, 0);

                    for( int i = 0; i < option; i++ )
                    {
                        if( checkFocusMouse( x_mouse, y_mouse, pos_option[i] ) )
                        {
                            return i;
                        }
                    }

                    break;

                case SDL_KEYDOWN:
                    if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        return 1;
                    }

                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        speed -= 4;

        // render background start
        start.render( gRenderer, speed, 0 );
        start.render( gRenderer, SCREEN_WIDTH + speed, 0 );

        if( -speed == SCREEN_WIDTH ) speed = 0;

        // render logo
        logo.render( gRenderer, 95, 130 );

        // render play_rect
        play_rect[0].render( gRenderer, pos_option[0].x, pos_option[0].y);
        play_rect[1].render( gRenderer, pos_option[1].x, pos_option[1].y);

        // render text
        text_option[0].renderText( gRenderer, pos_option[0].x + 28, pos_option[0].y + 23 );
        text_option[1].renderText( gRenderer, pos_option[1].x + 34, pos_option[1].y + 23 );

        SDL_RenderPresent( gRenderer );
    }

    return 1;
}

int Menu::showTapPlay( SDL_Renderer* gRenderer )
{
    // load background cho man hinh start
    if( !start.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background start texture!\n" );
		return 1;
	}

    // load get_ready cho tab_play
    if( !get_ready.loadFromFile( "image/get_ready.png", gRenderer ) )
	{
		printf( "Failed to load get_ready texture!\n" );
		return 1;
	}

	// load tap
    if( !tap.loadFromFile( "image/tap.png", gRenderer ) )
	{
		printf( "Failed to load tap texture!\n" );
		return 1;
	}

	while(true)
    {
        while( SDL_PollEvent( &mouse_event ) != 0 )
        {
            switch( mouse_event.type )
            {
                case SDL_QUIT:
                    return 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    return 0;
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        speed -= 4;

        // render background start
        start.render( gRenderer, speed, 0 );
        start.render( gRenderer, SCREEN_WIDTH + speed, 0 );

        if( -speed == SCREEN_WIDTH ) speed = 0;

        // render get_ready
        get_ready.render( gRenderer, 0, 100 );

        // render tap
        tap.render( gRenderer, ( SCREEN_WIDTH - tap.getWidth() ) / 2, 400 );

        SDL_RenderPresent( gRenderer );
    }

    return 1;
}

void Menu::showGameOver( SDL_Renderer* gRenderer )
{
    // load background cho man hinh gameover
    if( !start.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background gameover texture!\n" );
		//return 1;
	}

	// load background cho man hinh gameover
    if( !gameover.loadFromFile( "image/gameover.png", gRenderer ) )
	{
		printf( "Failed to load gameover texture!\n" );
		//return 1;
	}

	start.render( gRenderer, 0, 0 );
	gameover.render( gRenderer, 130, 150 );

	SDL_Delay(2000);
}
