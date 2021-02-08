#pragma once
#include <raylib\include\raylib.h>

//----------------------------------------------------------

#ifdef EXECUTE_TESTS
#include "temper\temper.h"
int main( int argc, char* argv[] )
{
    TEMPER_RUN(argc, argv);
    return TEMPER_GET_EXIT_CODE();
}
#else
int main( int argc, char* argv[] )
{
    int screenWidth = 1600;
    int screenHeight = 900;

    InitWindow( screenWidth, screenHeight, "Temper2 Entry" );
    SetTargetFPS( 60 );

    while( !WindowShouldClose() ) // responds to ESC key and close window button
    {
        BeginDrawing();
        ClearBackground( BLACK );
        DrawText( "This is the example project for the temper 2 game jam.", 20, 20, 20, GREEN );
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#endif

//----------------------------------------------------------