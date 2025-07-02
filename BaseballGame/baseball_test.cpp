#include"gmock/gmock.h"
#include"baseball.cpp"

using namespace testing;

TEST(BaseballGame, ThrowExceptionWhenInputLengthIsUnmached) {
	Baseball game;
	EXPECT_THROW(game.guess(string("12")), length_error);
}

int main() {
	InitGoogleMock();
	return RUN_ALL_TESTS();
}