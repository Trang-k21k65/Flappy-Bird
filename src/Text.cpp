#include "Text.h"

Text::Text()
{
    x_text = 50;
    y_text = 25;

    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;

    gFont = NULL;
}

Text::~Text()
{
    text.free();

    TTF_CloseFont( gFont );
	gFont = NULL;

	TTF_Quit();
}

void Text::setColor( const int& type )
{
    if( type == WHITE_TEXT )
    {
        textColor = { 255, 255, 255 };
    }

    if( type == ORANGE_TEXT )
    {
        textColor = { 255, 117, 26 };
    }

    if( type == RED_TEXT )
    {
        textColor = { 255, 51, 0 };
    }
}

bool Text::loadText( string s, SDL_Renderer* gRenderer )
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 20 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		if( !text.loadFromRenderedText( s, textColor, gRenderer, gFont ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

	return success;
}

void Text::renderText( SDL_Renderer* gRenderer )
{
    text.render( gRenderer, x_text, y_text);
}
