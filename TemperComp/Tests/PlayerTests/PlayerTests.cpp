#pragma once
#ifdef EXECUTE_TESTS

#include <temper/temper.h>

#include "Source/Player/Player.h"

static Player* TestablePlayer;

void PlayerPreTestSetup()
{
	printf( "PlayerPreTestSetup called \n" );
	TestablePlayer = new Player();
}

void PlayerPostTestTeardown()
{
	printf( "PlayerPostTestTeardown called \n" );
	delete TestablePlayer;
	TestablePlayer = nullptr;
}

#define PLAYER_TEST( testName ) TEMPER_TEST_C( testName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN )
#define PLAYER_PARAMETRIC(TestName, ...) TEMPER_PARAMETRIC_C( TestName, PlayerPreTestSetup, PlayerPostTestTeardown, TEMPER_FLAG_SHOULD_RUN, __VA_ARGS__ )

PLAYER_PARAMETRIC( Player_ProvidedInput_InterpretsDirectionCoorectly, const KeyboardKey Key, const EPlayerMove StartingDir, const EPlayerMove ExpectedResult )
{
	TEMPER_CHECK_TRUE( false );
}

TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric1, KeyboardKey::KEY_UP, EPlayerMove::MoveDown, EPlayerMove::MoveDown );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric2, KeyboardKey::KEY_UP, EPlayerMove::MoveLeft, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric3, KeyboardKey::KEY_UP, EPlayerMove::MoveRight, EPlayerMove::MoveUp );
TEMPER_INVOKE_PARAMETRIC_TEST( Player_ProvidedInput_InterpretsDirectionCoorectly, PlayerParamtric4, KeyboardKey::KEY_UP, EPlayerMove::MoveUp, EPlayerMove::MoveUp );

PLAYER_TEST( FirstTest )
{
	TEMPER_CHECK_TRUE( true );
}

PLAYER_TEST( SecondTest )
{
	TEMPER_CHECK_TRUE( true );
}

PLAYER_TEST( ThirdTest )
{
	TEMPER_CHECK_TRUE( true );
}

#endif // EXECUTE_TESTS
