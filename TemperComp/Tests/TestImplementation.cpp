#pragma once

#ifdef EXECUTE_TESTS

#define TEMPER_IMPLEMENTATION
#include <temper/temper.h>

TEMPER_TEST( SomeTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE( true );
}

TEMPER_TEST( AnotherRandomTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE( true );
}

TEMPER_TEST( RandomTest, TEMPER_FLAG_SHOULD_RUN ) {
	TEMPER_CHECK_TRUE( true );
}

#endif // EXECUTE_TESTS