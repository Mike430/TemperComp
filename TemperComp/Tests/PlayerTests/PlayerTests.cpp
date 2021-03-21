#pragma once
#ifdef EXECUTE_TESTS

#include <temper/temper.h>

#include "Source/Player/Player.h"

//==========================================================
// FIXTURES
//==========================================================

static Player* g_testPlayer;

//----------------------------------------------------------

struct PlayerTestHelpers
{
public:
	static void SetPlayerMoveStates( Player* playerPtr, const EPlayerMove previous, const EPlayerMove current )
	{
		playerPtr->m_moveStatePrevious = previous;
		playerPtr->m_moveState = current;
	}

	static const EPlayerMove GetPlayerCurrentMoveState( Player* playerPtr )
	{
		return playerPtr->m_moveState;
	}

	static const float GetPlayerMoveTimer( Player* playerPtr )
	{
		return playerPtr->m_moveTimer;
	}

	static void TestHandleInput( Player* playerPtr )
	{
		playerPtr->HandleInput();
	}

	static void SetPlayerBodyParts( Player* playerPtr, std::vector<Vec2D> newBodyParts )
	{
		TEMPER_CHECK_TRUE_AM( newBodyParts.size() < playerPtr->m_maxBodyPartsCount, "Attempted to assign an array of body parts greater than what the player can have" );
		playerPtr->m_bodyPartsCount = ( int ) newBodyParts.size();

		for( int i = 0; i < newBodyParts.size(); ++i )
		{
			playerPtr->m_bodyParts[ i ] = newBodyParts[ i ];
		}
	}

	static bool GetShouldDie( Player* playerPtr )
	{
		return playerPtr->ShouldDie();
	}
};

//----------------------------------------------------------

void PlayerPreTestSetup()
{
	printf( "PlayerPreTestSetup called \n" );
	g_testPlayer = new Player( 200, 200 ); // for tests we only need a 4 x 4 grid
}

//----------------------------------------------------------

void PlayerPostTestTeardown()
{
	printf( "PlayerPostTestTeardown called \n" );
	delete g_testPlayer;
	g_testPlayer = nullptr;
}

//==========================================================
// TEST MACRO OVERLOADS
//==========================================================

#define PLAYER_TEST( testName ) TEMPER_TEST_C( testName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN )
#define PLAYER_PARAMETRIC( TestName, ... ) TEMPER_PARAMETRIC_C( TestName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN, __VA_ARGS__ )

//==========================================================
// TESTS
//==========================================================

PLAYER_PARAMETRIC( Player_ProvidedInput_InterpretsDirectionCoorectly, const KeyboardKey key, const EPlayerMove startingDir, const EPlayerMove expectedResult )
{
	g_testPlayer->FakeKeyPressed = key;
	PlayerTestHelpers::SetPlayerMoveStates( g_testPlayer, startingDir, startingDir );
	PlayerTestHelpers::TestHandleInput( g_testPlayer );

	const EPlayerMove currentMoveState = PlayerTestHelpers::GetPlayerCurrentMoveState( g_testPlayer );
	TEMPER_CHECK_EQUAL_M( currentMoveState,
						  expectedResult,
						  "The player's movement state (%d) doesn't match the expected output(%d).",
						  currentMoveState,
						  expectedResult );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_UP, EPlayerMove::MoveDown, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_UP, EPlayerMove::MoveLeft, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_UP, EPlayerMove::MoveRight, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_UP, EPlayerMove::MoveUp, EPlayerMove::MoveUp );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_DOWN, EPlayerMove::MoveDown, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_DOWN, EPlayerMove::MoveLeft, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_DOWN, EPlayerMove::MoveRight, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_DOWN, EPlayerMove::MoveUp, EPlayerMove::MoveUp );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_LEFT, EPlayerMove::MoveDown, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_LEFT, EPlayerMove::MoveLeft, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_LEFT, EPlayerMove::MoveRight, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_LEFT, EPlayerMove::MoveUp, EPlayerMove::MoveLeft );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveDown, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveLeft, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveRight, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveUp, EPlayerMove::MoveRight );

//----------------------------------------------------------

PLAYER_PARAMETRIC( Player_PlayerMoveDirection_MovesAppropriatelyOnUpdate, const EPlayerMove moveDir, const Vec2D expectedDelta )
{
	const float moveTimer = PlayerTestHelpers::GetPlayerMoveTimer( g_testPlayer );
	const Vec2D startingPosition = g_testPlayer->GetPosition();

	PlayerTestHelpers::SetPlayerMoveStates( g_testPlayer, moveDir, moveDir );
	g_testPlayer->Update( moveTimer * 1.5f );

	const Vec2D endingPosition = g_testPlayer->GetPosition();
	const Vec2D actualDelta = endingPosition - startingPosition;
	TEMPER_CHECK_TRUE_M( actualDelta == expectedDelta,
						 "Vec2D(%.3f, %.3f) doesn't match Vec2D(%.3f, %.3f). Movement is broken\n",
						 actualDelta.x, actualDelta.y,
						 expectedDelta.x, expectedDelta.y );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( Player_PlayerMoveDirection_MovesAppropriatelyOnUpdate, EPlayerMove::MoveUp, Vec2D( 0.f, -50.f ) );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_PlayerMoveDirection_MovesAppropriatelyOnUpdate, EPlayerMove::MoveDown, Vec2D( 0.f, 50.f ) );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_PlayerMoveDirection_MovesAppropriatelyOnUpdate, EPlayerMove::MoveLeft, Vec2D( -50.f, 0.f ) );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_PlayerMoveDirection_MovesAppropriatelyOnUpdate, EPlayerMove::MoveRight, Vec2D( 50.f, 0.f ) );

//----------------------------------------------------------

PLAYER_TEST( PlayerWithBodyLength3_GetAvailablePositionsCalled_ArrayIsOfCorrectSizeAndSpec )
{
	// free cells are marked F, taken cells are marked with P for player and a number for the body part index.
	// F, F, F, F
	// F, 1, P, F
	// F, 2, F, F
	// F, 3, F, F

	const size_t expectedAvailableSpaces = 12;
	g_testPlayer->SetPosition( Vec2D( 50.f, 0.f ) );
	std::vector<Vec2D> newBody;
	newBody.push_back( Vec2D( 0.f, 0.f ) );
	newBody.push_back( Vec2D( 0.f, 50.f ) );
	newBody.push_back( Vec2D( 0.f, 100.f ) );
	PlayerTestHelpers::SetPlayerBodyParts( g_testPlayer, newBody );

	const std::vector<Vec2D> availablePositions = g_testPlayer->GetAvailableCellsPositions();
	TEMPER_CHECK_EQUAL_M( availablePositions.size(),
						  expectedAvailableSpaces,
						  "The number of available spaces was wrong (%d != %d), the availability check is broken\n",
						  availablePositions.size(),
						  expectedAvailableSpaces );

	const Vec2D playerPosition = g_testPlayer->GetPosition();

	for( const Vec2D& availableSpot : availablePositions )
	{
		TEMPER_CHECK_NOT_EQUAL_M( availableSpot, playerPosition, "An available cell is overlapping the player. Pickups may spawn ontop of us." );

		for( const Vec2D& bodyPart : newBody )
		{
			TEMPER_CHECK_NOT_EQUAL_M( availableSpot, bodyPart, "An available cell is overlapping a body part. Pickups may spawn ontop of out tail." );
		}
	}
}

//----------------------------------------------------------

PLAYER_TEST( PlayerWithBodyLength3_ExtraBodyPartGranted_ExtraPartUpdates )
{
}

//----------------------------------------------------------

PLAYER_TEST( Player_OutOfBounds_ShouldDieIsTrue )
{
	PlayerTestHelpers::SetPlayerBodyParts( g_testPlayer, std::vector<Vec2D>() ); // give the player an empty array so we aren't overlapping ourselves
	TEMPER_CHECK_FALSE_M( PlayerTestHelpers::GetShouldDie( g_testPlayer ), "The player should start in the centre of the screen and not be out of bounds.\n" );

	g_testPlayer->SetPosition( Vec2D( 0.f, 150.f ) );
	TEMPER_CHECK_TRUE_M( PlayerTestHelpers::GetShouldDie( g_testPlayer ), "The player should off the bottom of the screen and so should be dead.\n" );

	g_testPlayer->SetPosition( Vec2D( 0.f, -100.f ) );
	TEMPER_CHECK_TRUE_M( PlayerTestHelpers::GetShouldDie( g_testPlayer ), "The player should off the top of the screen and so should be dead.\n" );

	g_testPlayer->SetPosition( Vec2D( -100.f, 0.f ) );
	TEMPER_CHECK_TRUE_M( PlayerTestHelpers::GetShouldDie( g_testPlayer ), "The player should off the left of the screen and so should be dead.\n" );

	g_testPlayer->SetPosition( Vec2D( 150.f, 0.f ) );
	TEMPER_CHECK_TRUE_M( PlayerTestHelpers::GetShouldDie( g_testPlayer ), "The player should off the right of the screen and so should be dead.\n" );
}

//----------------------------------------------------------

PLAYER_TEST( PlayerWithBodyLength3_OverlapsBodyPart_ShouldDieIsTrue )
{
}

//----------------------------------------------------------

#endif // EXECUTE_TESTS
