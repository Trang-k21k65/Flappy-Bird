#include "Game.h"
#include <iostream>

using namespace std;

int main( int argc, char* args[] )
{
    Game gGame;

    if( !gGame.init() )
    {
        cout << "Failed to initialize!\n" ;
    }

    if( !gGame.loadImage() )
    {
        cout << "Failed to load image!\n";
    }

    if( !gGame.loadMixer() )
    {
        cout << "Failed to load mixer!\n";
    }

    gGame.gameRender();

   /* bool check = gGame.isGameOver();
    if( check == false ) load anh Gameover

*/
    return 0;
}



