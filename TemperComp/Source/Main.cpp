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

#include "Source/Player/Player.h"
#include "Source/Managers/ScoreManager.h"

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

//----------------------------------------------------------

typedef std::chrono::duration<float> floatSeconds;
typedef std::chrono::duration<int, std::micro> intMicroseconds;

bool shutdownRequested = false;
int32_t g_sceenWidth = 900;
int32_t g_sceenHeight = 900;
float g_targetFPS = 60.0f;
float g_frameLength = 1.0f / g_targetFPS;
float g_secondsToSleep = 0.0f;
std::chrono::high_resolution_clock g_timer;
std::chrono::high_resolution_clock::time_point g_frameStart;
std::chrono::high_resolution_clock::time_point g_frameEnd;
floatSeconds g_timeToUpdate;
floatSeconds g_deltaSeconds;
intMicroseconds g_sleepDuration;
Vector2 g_upperLeftCorner;
Camera2D g_localCamera2D;
std::vector<GameObject*> g_scene;
Player* g_player = nullptr;

//----------------------------------------------------------

void PresentMainMenu()
{
	DrawRectangle( -g_sceenWidth / 2,
				   -g_sceenHeight / 2,
				   g_sceenWidth,
				   g_sceenHeight,
				   { 0, 0, 0, 100 } );

	DrawText( "P - play\nE - exit", 0, 0, 20, GREEN );

	if ( IsKeyPressed( KeyboardKey::KEY_P ) )
	{
		g_scene.clear();
		g_player = new Player( g_sceenWidth, g_sceenHeight );
		g_scene.push_back( g_player );

		ScoreManager* scoreManager = ScoreManager::GetInstance();
		scoreManager->SetPlayer( g_player );
	}

	shutdownRequested = IsKeyReleased( KeyboardKey::KEY_E );
}

//----------------------------------------------------------

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

	g_upperLeftCorner = { -g_sceenWidth * 0.5f, -g_sceenHeight * 0.5f };
	g_localCamera2D = { 0.0f, 0.0f, g_upperLeftCorner.x, g_upperLeftCorner.y, 0.0f, 1.0f };

	ScoreManager* scoreManager = ScoreManager::GetInstance();

	// GAME LOOP
	while ( !WindowShouldClose() && shutdownRequested == false ) // responds to ESC key and close window button
	{
		// TIMINGS
		g_frameStart = g_timer.now();

		// UPDATE
		for ( GameObject* gameObject : g_scene )
		{
			gameObject->Update( g_deltaSeconds.count() );
		}

		// DRAW
		BeginDrawing();
		BeginMode2D( g_localCamera2D );
		ClearBackground( BLACK );

		for ( GameObject* gameObject : g_scene )
		{
			gameObject->Draw();
		}

		Vec2D pickupPosition = scoreManager->GetPickupPosition();
		DrawCircle( ( int32_t ) pickupPosition.x - 25,
					( int32_t ) pickupPosition.y - 25,
					25,
					{ 182, 3, 252, 255 } );

		// MainMenu & UI
		if ( g_player == nullptr || g_player->HasDied() )
		{
			PresentMainMenu();
		}

		std::string scoreText = "Your score: ";
		std::string fpsText =   "FPS: ";
		int32_t FPS = ( int32_t ) ( 1.0f / g_deltaSeconds.count() );
		scoreText += std::to_string( scoreManager->GetScore() );
		fpsText += std::to_string( FPS );
		DrawText( scoreText.c_str(), ( int32_t ) g_upperLeftCorner.x, ( int32_t ) g_upperLeftCorner.y, 20, GREEN );
		DrawText( fpsText.c_str(), ( int32_t ) g_upperLeftCorner.x, ( int32_t ) g_upperLeftCorner.y + 30, 20, GREEN );

		EndMode2D();
		EndDrawing();

		// TIMINGS
		g_frameEnd = g_timer.now();
		g_timeToUpdate = g_frameEnd - g_frameStart;

		g_secondsToSleep = g_frameLength - g_timeToUpdate.count();
		g_sleepDuration = std::chrono::duration_cast< intMicroseconds >( floatSeconds( g_secondsToSleep ) );
		std::this_thread::sleep_for( g_sleepDuration );

		g_frameEnd = g_timer.now();
		g_deltaSeconds = g_frameEnd - g_frameStart;
	}

	for ( GameObject* gameObject : g_scene )
	{
		delete gameObject;
	}

	CloseWindow();
	return 0;
}
#endif

//----------------------------------------------------------