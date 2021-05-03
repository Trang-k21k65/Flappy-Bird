#include "Game.h"

Game::Game()
{
    score_val = 0;
    best_score = 0;

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
    for( int i = 0; i < 4; i++)
    {
        Mix_FreeChunk( gMusic[i] );
    }

    for( int i = 0; i < 4; i++)
    {
        gMusic[i] = NULL;
    }

    //Free loaded images
	gBackground.free();
	play.free();
	pause.free();

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

// hàm khởi tạo window, bút vẽ, thư viện ảnh & kiểu ảnh, thư viện font chữ, thư viện mixer
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
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );

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

// hàm load ảnh trong màn hình chơi chính
bool Game::loadImage()
{
    bool success = true;

    // load background
    if( !gBackground.loadFromFile( "image/bgr.png", gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	// load icon ở trạng thái đang chơi
    if( !play.loadFromFile( "image/play_icon.png", gRenderer ) )
	{
		printf( "Failed to load play_icon texture!\n" );
		success = false;
	}

	// load icon ở trạng thái pause
    if( !pause.loadFromFile( "image/pause_icon.png", gRenderer ) )
	{
		printf( "Failed to load pause_icon texture!\n" );
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

// hàm load âm thanh
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
	gMusic[2] = Mix_LoadWAV( "mixer/score.wav" );
	if( gMusic[2] == NULL )
	{
		printf( "Failed to load score sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load collision sound effect
	gMusic[3] = Mix_LoadWAV( "mixer/collision.wav" );
	if( gMusic[3] == NULL )
	{
		printf( "Failed to load collision sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    return success;
}

// hàm viết chương trình chính trong game
void Game::gamePlay()
{
    // variables adjust gameloop
    bool play_again = 1; // 1: chơi tiếp; 0: thoát
    bool quit = false;
    SDL_Event e;

    // show màn hình start lúc bắt đầu game
    int start_menu = gMenu.showStart( gRenderer, gMusic[0] );
    if( start_menu == 1 )
    {
        quit = true;
    }

    // vòng lặp do-while để chọn chơi lại hay thoát game
    do
    {
        // show màn hình tap play
        int tap_play_menu = gMenu.showTapPlay( gRenderer );
        if( tap_play_menu == 1 )
        {
            quit = true;
        }

        // set feature for threat(cot)
        gThreat[0].set_threat_height();
        gThreat[1].set_threat_height();
        gThreat[2].set_threat_height();

        // set co-ordinate at first for bird
        gBird.set_x_bird( 150 );
        gBird.set_y_bird( 150 );

        // variable denotes speed of background at main play screen
        int x = 0;

        // variables denote score
        gScore.setColor( Text::WHITE_TEXT );
        score_val = 0;
        string score, best;
        bool collision = false; // biến = false nếu bird không va chạm với rect điểm; = true nếu va chạm
        bool addScore = true; // biến kiểm tra xem điểm có cộng thêm hay không

        // variables denote play/pause
        SDL_Rect icon_rect = { 50, 50, 40, 40 };
        int xpos = 0, ypos = 0; // tọa độ chuột trên màn hình
        int count = 0; // count chẵn thì ở trạng thái play; count lẻ thì ở trạng thái pause

        //While gameloop is running
        while( !quit )
        {
            //Handle events
            while( SDL_PollEvent(&e) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                if( e.type == SDL_MOUSEMOTION )
                {
                    SDL_GetMouseState( &xpos, &ypos );

                    if( checkFocusMouse( xpos, ypos, icon_rect ) )
                    {
                        gBird.is_click_icon = true;
                    }
                    else gBird.is_click_icon = false;
                }

                if( e.type == SDL_MOUSEBUTTONDOWN )
                {
                    SDL_GetMouseState( &xpos, &ypos );

                    if( checkFocusMouse( xpos, ypos, icon_rect ) )
                    {
                        Mix_PlayChannel( -1, gMusic[0], 0 );
                        count++;
                    }
                }

                gBird.handleEvents( e, gMusic[1] );
            }

            SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
            SDL_RenderClear( gRenderer );

            if( count % 2 == 1 ) x -= 0;
            else x -= 4;

            // render background
            gBackground.render( gRenderer, x, 0 );
            gBackground.render( gRenderer, SCREEN_WIDTH + x, 0 );

            if( -x == SCREEN_WIDTH ) x = 0;

            // render threat(cot)
            if( gThreat[0].x_threat >= 0 )
            {
                gThreat[1].x_threat = gThreat[0].x_threat + SCREEN_WIDTH / 3;
                gThreat[2].x_threat = gThreat[1].x_threat + SCREEN_WIDTH / 3;
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

            // render play, pause icon and handle play/pause option
            play.render( gRenderer, icon_rect.x, icon_rect.y );
            if( count % 2 == 1 )
            {
                pause.render( gRenderer, icon_rect.x, icon_rect.y );
                for( int i = 0; i < 3; i++ )
                {
                    gThreat[i].pause_threat = true;
                }
                gBird.pause_bird = true;
            }
            else
            {
                play.render( gRenderer, icon_rect.x, icon_rect.y );
                for( int i = 0; i < 3; i++ )
                {
                    gThreat[i].pause_threat = false;
                }
                gBird.pause_bird = false;
            }

            // render bird
            gBird.renderBird( gRenderer );
            gBird.handleMoveBird();

            // check collision between bird and threat(cot)
            for( int i = 0; i < 3; i++ )
            {
                bool check1 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol1() );
                bool check2 = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectCol2() );
                if( check1 || check2 || gBird.isDie() == true )
                {
                    Mix_PlayChannel( -1, gMusic[3] , 0);
                    quit = true;
                    break;
                }
            }

            // xử lí điểm
            for( int i = 0; i < 3; i++ )
            {
                bool check = gBird.checkCollision( gBird.get_RectBird(), gThreat[i].get_RectBlank() );
                if( check == true )
                {
                    collision = true;
                    break;
                }
                else collision = false;
            }

            if( collision == true )
            {
                if( addScore == true )
                {
                    score_val++;
                    Mix_PlayChannel( -1, gMusic[2], 0);
                }
                addScore = false;
            }
            else addScore = true;

            score = to_string( score_val );

            // hiển thị điểm trên màn hình
            gScore.loadText( score, gRenderer, 50 );
            gScore.renderText( gRenderer, SCREEN_WIDTH / 2, 100 );

            SDL_RenderPresent( gRenderer );
        }

        if( best_score < score_val ) best_score = score_val;
        best = to_string( best_score );

        // hiển thị màn hình gameover khi chơi thua
        int gameover_menu = gMenu.showGameOver( gRenderer, gMusic[0], score , best );

        if( gameover_menu == 0 )
        {
            quit = false;
            play_again = 1;
        }
        else play_again = 0;

    }while( play_again != 0 );
}
