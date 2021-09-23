#include "pch.h"
#include "../BowlingProblem/ScoreCalculator.h"
using namespace std;


TEST(ScoreCalculator, NoBalls) {

	vector<int> frames{ };

	vector<int> score = ScoreCalculator::score(frames);

	vector<int> expected{};

	EXPECT_EQ(expected, score);
}

TEST(ScoreCalculator, ScoreOneBallZero) {

	vector<int> frames{ 0 };

	vector<int> score = ScoreCalculator::score(frames);

	ASSERT_EQ(1, score.size());
	EXPECT_EQ(0, score[0]);
}



//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
TEST(ScoreCalculator, ScoreOneBall_5) { 

	vector<int> frames{ 5 };

	vector<int> score = ScoreCalculator::score(frames);

	ASSERT_EQ(1, score.size());
	EXPECT_EQ(5, score[0]);
}




//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
TEST(ScoreCalculator, Score_6_2) {

	vector<int> frames{ 6, 2};

	vector<int> score = ScoreCalculator::score(frames);

	vector<int> expected{ 8 };

	EXPECT_EQ(expected, score);
}


//
//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
TEST(ScoreCalculator, Score_6_2_5) {

	vector<int> frames{ 6, 2, 5 };

	vector<int> score = ScoreCalculator::score(frames);

	vector<int> expected{ 8, 13 };

	EXPECT_EQ(expected, score);
}




//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
TEST(ScoreCalculator, Score_6_2_5_4_3) {

	vector<int> frames{ 6, 2, 5, 4, 3 };

	vector<int> score = ScoreCalculator::score(frames);

	vector<int> expected{ 8, 17, 20};

	EXPECT_EQ(expected, score);
}



//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
TEST(ScoreCalculator, Score_6_4_5_Spare) {

	vector<int> frames{ 6, 4, 5};

	vector<int> score = ScoreCalculator::score(frames);

	vector<int> expected{ 15, 20 };

	EXPECT_EQ(expected, score);
}
//
//



//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_10_5_4_Strike) {
//
//	vector<int> frames{ 10, 5, 4 };
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 19, 28 };
//
//	EXPECT_EQ(expected, score);
//}
//



//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_10_10_2Strikes) {
//
//	vector<int> frames{ 10, 10 };
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 20, 30 };
//
//	EXPECT_EQ(expected, score);
//}

//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_10_10_10_4Strikes) {
//
//	vector<int> frames{ 10, 10, 10, 10};
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 30, 60, 80, 90 };
//
//	EXPECT_EQ(expected, score);
//}
//


//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_FullGame) {
//
//	vector<int> frames{ 10, 7, 3, 9, 0, 10, 0, 8, 8,2, 0, 6, 10, 10, 10, 8, 1 };
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 20, 39, 48, 66, 74, 84, 90, 120, 148, 167 };
//
//	EXPECT_EQ(expected, score);
//}
//


//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_PerfectGame) {
//
//	vector<int> frames{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 30, 60, 90, 120, 150, 180, 210, 240, 270, 300 };
//
//	EXPECT_EQ(expected, score);
//}
//


//Uncomment this test ONLY if all previous test have passed
//DO NOT change the test!
//TEST(ScoreCalculator, Score_tooManyFrames) {
//
//	vector<int> frames{ 10, 7, 3, 9, 0, 10, 0, 8, 8,2, 0, 6, 10, 10, 10, 8, 1, 10, 10};
//
//	vector<int> score = ScoreCalculator::score(frames);
//
//	vector<int> expected{ 20, 39, 48, 66, 74, 84, 90, 120, 148, 167 };
//
//	EXPECT_EQ(expected, score);
//}
//
