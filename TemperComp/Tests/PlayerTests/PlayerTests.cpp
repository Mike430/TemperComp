#pragma once
#include <temper/temper.h>

#define PLAYER_TEST( testName ) TEMPER_TEST( testName, TEMPER_FLAG_SHOULD_RUN )

PLAYER_TEST( FirstTest )
{
	TEMPER_CHECK_TRUE( true );
}