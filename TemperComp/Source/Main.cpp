#pragma once
#include "Player/Player.h"

//----------------------------------------------------------
// Snake was originally released in 1976 and thus will cost
// you 20 points if you attempt to make this your submission
// entry. MWAHAAHA!
// citation = https://en.wikipedia.org/wiki/Snake_(video_game_genre)#:~:text=Snake%20%E2%80%93%20The%20first%20published%20by,introduced%20on%20the%20Nokia%206110.
// 
// Disclaimer:
// Even though there are no points for code clenliness, I
// hope (nay PRAY) you don't commit some of the same sins
// I'm commiting in this example project. No one should ever
// hard-code a fame's deltatime. I'm on a tight schedule RN.
//----------------------------------------------------------

int g_sceenWidth = 1600;
int g_sceenHeight = 900;
int g_targetFPS = 60;
float g_deltaTime = 1.0f / g_targetFPS; // Write a disclaimer... I feel ill!
Vector2 g_upperLeftCorner;
Camera2D g_localCamera2D;
std::vector<GameObject*> g_scene;

#ifdef EXECUTE_TESTS

#include "temper\temper.h"

int main( int argc, char* argv[] )
{
	TEMPER_RUN( argc, argv );
	return TEMPER_GET_EXIT_CODE();
}
#else
int main( int argc, char* argv[] )
{
	InitWindow( g_sceenWidth, g_sceenHeight, "This is the example project for the temper 2 game jam" );
	SetTargetFPS( g_targetFPS );

	g_upperLeftCorner = { -g_sceenWidth * 0.5f, -g_sceenHeight * 0.5f };
	g_localCamera2D = { 0.0f, 0.0f, g_upperLeftCorner.x, g_upperLeftCorner.y, 0.0f, 1.0f };

	g_scene.push_back( new Player() );

	// GAME LOOP
	while( !WindowShouldClose() ) // responds to ESC key and close window button
	{
		// UPDATE
		for( GameObject* gameObject : g_scene )
		{
			gameObject->Update( g_deltaTime );
		}

		// DRAW
		BeginDrawing();
		BeginMode2D( g_localCamera2D );
		ClearBackground( BLACK );

		for( GameObject* gameObject : g_scene )
		{
			gameObject->Draw();
		}

		DrawText( "Your score: 0", ( int ) g_upperLeftCorner.x, ( int ) g_upperLeftCorner.y, 20, GREEN );

		EndMode2D();
		EndDrawing();
	}

	for( GameObject* gameObject : g_scene )
	{
		delete gameObject;
	}

	CloseWindow();
	return 0;
}
#endif

//----------------------------------------------------------