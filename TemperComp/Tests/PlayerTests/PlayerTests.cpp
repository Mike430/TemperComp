#pragma once
#ifdef EXECUTE_TESTS

#include <temper/temper.h>

#include "Source/Player/Player.h"

//==========================================================
// FIXTURES
//==========================================================

static Player* TestablePlayer;

//----------------------------------------------------------

struct PlayerTestHelperFunctions
{
public:

	static void SetPlayerMoveStates( Player* PlayerPtr, const EPlayerMove previous, const EPlayerMove current )
	{
		PlayerPtr->m_moveStatePrevious = previous;
		PlayerPtr->m_moveState = current;
	}

	static const EPlayerMove GetPlayerCurrentMoveState( Player* PlayerPtr )
	{
		return PlayerPtr->m_moveState;
	}

	static void TestHandleInput( Player* PlayerPtr )
	{
		PlayerPtr->HandleInput();
	}
};

//----------------------------------------------------------

void PlayerPreTestSetup()
{
	printf( "PlayerPreTestSetup called \n" );
	TestablePlayer = new Player();
}

//----------------------------------------------------------

void PlayerPostTestTeardown()
{
	printf( "PlayerPostTestTeardown called \n" );
	delete TestablePlayer;
	TestablePlayer = nullptr;
}

//==========================================================
// TEST MACRO OVERLOADS
//==========================================================

#define PLAYER_TEST( testName ) TEMPER_TEST_C( testName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN )
#define PLAYER_PARAMETRIC(TestName, ...) TEMPER_PARAMETRIC_C( TestName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN, __VA_ARGS__ )

//==========================================================
// TESTS
//==========================================================

PLAYER_PARAMETRIC( Player_ProvidedInput_InterpretsDirectionCoorectly, const KeyboardKey Key, const EPlayerMove StartingDir, const EPlayerMove ExpectedResult )
{
	TestablePlayer->FakeKeyPressed = Key;
	PlayerTestHelperFunctions::SetPlayerMoveStates( TestablePlayer, StartingDir, StartingDir );
	PlayerTestHelperFunctions::TestHandleInput( TestablePlayer );
	
	const EPlayerMove CurrentMoveState = PlayerTestHelperFunctions::GetPlayerCurrentMoveState( TestablePlayer );
	TEMPER_CHECK_EQUAL_M( CurrentMoveState,
						  ExpectedResult,
						  "The player's movement state (%d) doesn't match the expected output(%d).",
						  CurrentMoveState,
						  ExpectedResult );
}

//----------------------------------------------------------

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric1, KeyboardKey::KEY_UP, EPlayerMove::MoveDown, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric2, KeyboardKey::KEY_UP, EPlayerMove::MoveLeft, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric3, KeyboardKey::KEY_UP, EPlayerMove::MoveRight, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric4, KeyboardKey::KEY_UP, EPlayerMove::MoveUp, EPlayerMove::MoveUp );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric5, KeyboardKey::KEY_DOWN, EPlayerMove::MoveDown, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric6, KeyboardKey::KEY_DOWN, EPlayerMove::MoveLeft, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric7, KeyboardKey::KEY_DOWN, EPlayerMove::MoveRight, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric8, KeyboardKey::KEY_DOWN, EPlayerMove::MoveUp, EPlayerMove::MoveUp );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric9, KeyboardKey::KEY_LEFT, EPlayerMove::MoveDown, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric10, KeyboardKey::KEY_LEFT, EPlayerMove::MoveLeft, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric11, KeyboardKey::KEY_LEFT, EPlayerMove::MoveRight, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric12, KeyboardKey::KEY_LEFT, EPlayerMove::MoveUp, EPlayerMove::MoveLeft );

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric13, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveDown, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric14, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveLeft, EPlayerMove::MoveLeft );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric15, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveRight, EPlayerMove::MoveRight );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric16, KeyboardKey::KEY_RIGHT, EPlayerMove::MoveUp, EPlayerMove::MoveRight );

//----------------------------------------------------------

PLAYER_TEST( FirstTest )
{
	TEMPER_CHECK_TRUE( true );
}

//----------------------------------------------------------

PLAYER_TEST( SecondTest )
{
	TEMPER_CHECK_TRUE( true );
}

//----------------------------------------------------------

PLAYER_TEST( ThirdTest )
{
	TEMPER_CHECK_TRUE( true );
}

//----------------------------------------------------------

#endif // EXECUTE_TESTS
