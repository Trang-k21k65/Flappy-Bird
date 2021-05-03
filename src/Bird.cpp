#include "Bird.h"

Bird::Bird()
{
    speed_bird = 0;

    x_bird = 100;
    y_bird = 100;

    die = false;
    pause_bird = false;
    is_click_icon = false;
}

Bird::~Bird()
{
    bird.free();
    bird_animated.free();
}

/*void Bird::setAnimated( SDL_Renderer *gRenderer )
{
    if( !bird_animated.loadFromFile( "image/animated.png", gRenderer ) )
	{
		printf( "Failed to load bird_animated texture!\n" );
	}
	else
    {
        //Set frameClips
		frameClips[ 0 ].x =   0;
		frameClips[ 0 ].y =   0;
		frameClips[ 0 ].w = 100;
		frameClips[ 0 ].h = 100;

		frameClips[ 1 ].x = 100;
		frameClips[ 1 ].y =   0;
		frameClips[ 1 ].w = 100;
		frameClips[ 1 ].h = 100;

		frameClips[ 2 ].x = 200;
		frameClips[ 2 ].y =   0;
		frameClips[ 2 ].w = 100;
		frameClips[ 2 ].h = 100;

		frameClips[ 3 ].x = 300;
		frameClips[ 3 ].y =   0;
		frameClips[ 3 ].w = 100;
		frameClips[ 3 ].h = 100;
    }
}

void Bird::renderBird( SDL_Renderer *gRenderer )
{
    int current_frame = 0;

    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
    SDL_RenderClear( gRenderer );

    SDL_Rect* currentClip = &frameClips[ current_frame / 4 ];
    bird_animated.render( gRenderer, x_bird, y_bird, currentClip );

    current_frame++;

    if( current_frame / 4 >= frame )
    {
        current_frame = 0;
    }
}*/

void Bird::renderBird( SDL_Renderer *gRenderer )
{
    bird.render( gRenderer, x_bird, y_bird );
}

// hàm xử lí xự kiện cho con bird, khi bay lên thì sẽ có tiếng
void Bird::handleEvents( SDL_Event& event, Mix_Chunk* wing )
{
    // mouse event
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die && !pause_bird )
            {
                speed_bird = -4;
                if( !is_click_icon ) Mix_PlayChannel( -1, wing, 0);
            }
            else speed_bird = 0;
        }
    }

    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if( !die && !pause_bird ) speed_bird = 4;
            else speed_bird = 0;
        }
    }

    // keyboard event
    if( event.type == SDL_KEYDOWN )
    {
        if( event.key.keysym.sym == SDLK_SPACE )
        {
            if( !die && !pause_bird )
            {
                speed_bird = -4;
                Mix_PlayChannel( -1, wing, 0);
            }
            else speed_bird = 0;
        }
    }

    if( event.type == SDL_KEYUP )
    {
        if( event.key.keysym.sym == SDLK_SPACE )
        {
            if( !die && !pause_bird ) speed_bird = 4;
            else speed_bird = 0;
        }
    }

}

void Bird::handleMoveBird()
{
    if( !pause_bird ) y_bird += speed_bird;

    if( y_bird + 37 < 0 || y_bird + 61 > 640 )
    {
        die = true;
    }
}

// hàm kiểm tra va chạm giữa 2 rect
bool Bird::checkCollision( SDL_Rect rect1, SDL_Rect rect2 )
{
    bool success = false;

    if( ( rect1.x < rect2.x + rect2.w ) && ( rect1.x + rect1.w > rect2.x ) &&
        ( rect1.y < rect2.y + rect2.h ) && ( rect1.y + rect1.h > rect2.y ) )
    {
        success = true;
    }

    return success;
}

// hàm get rect của con bird
SDL_Rect Bird::get_RectBird()
{
    SDL_Rect rect;

    rect.x = x_bird + 28;
    rect.y = y_bird + 30;
    rect.w = 40;
    rect.h = 34;

    return rect;
}

