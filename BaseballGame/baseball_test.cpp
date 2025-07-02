#include"gmock/gmock.h"
#include"baseball.cpp"
using namespace testing;

TEST(BaseballGame, TryGameTest) {
	EXPECT_EQ(1, 1);
}

int main() {
	InitGoogleMock();
	return RUN_ALL_TESTS();
}