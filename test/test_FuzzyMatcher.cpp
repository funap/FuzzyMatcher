#include <gtest/gtest.h>
#include "FuzzyMatcher.h"

class FuzzyMatcherTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FuzzyMatcherTest, BasicMatching) {
    FuzzyMatcher matcher(L"abc");
    std::vector<size_t> positions;

    // Exact match
    EXPECT_GT(matcher.ScoreMatch(L"abc", &positions), 0);
    EXPECT_EQ(positions, std::vector<size_t>({0, 1, 2}));

    // Partial match
    positions.clear();
    EXPECT_GT(matcher.ScoreMatch(L"xaxbxc", &positions), 0);
    EXPECT_EQ(positions, std::vector<size_t>({1, 3, 5}));
}

TEST_F(FuzzyMatcherTest, CaseInsensitiveMatching) {
    FuzzyMatcher matcher(L"abc");
    std::vector<size_t> positions;

    EXPECT_GT(matcher.ScoreMatch(L"ABC", &positions), 0);
    EXPECT_GT(matcher.ScoreMatch(L"aBc", &positions), 0);
}

TEST_F(FuzzyMatcherTest, BonusScoring) {
    // First letter bonus
    {
        FuzzyMatcher matcher(L"a");
        std::vector<size_t> positions;
        int scoreStart = matcher.ScoreMatch(L"abc", &positions);
        int scoreMid = matcher.ScoreMatch(L"bac", &positions);
        EXPECT_GT(scoreStart, scoreMid);
    }

    // Camel case bonus
    {
        FuzzyMatcher matcher(L"c");
        std::vector<size_t> positions;
        int scoreCamel = matcher.ScoreMatch(L"testCase", &positions);
        int scoreNormal = matcher.ScoreMatch(L"testcase", &positions);
        EXPECT_GT(scoreCamel, scoreNormal);
    }
}

TEST_F(FuzzyMatcherTest, EdgeCases) {
    // Empty pattern
    {
        FuzzyMatcher matcher(L"");
        std::vector<size_t> positions;
        EXPECT_EQ(matcher.ScoreMatch(L"test", &positions), 0);
    }

    // Empty target
    {
        FuzzyMatcher matcher(L"test");
        std::vector<size_t> positions;
        EXPECT_EQ(matcher.ScoreMatch(L"", &positions), 0);
    }

    // Pattern longer than target
    {
        FuzzyMatcher matcher(L"toolong");
        std::vector<size_t> positions;
        EXPECT_EQ(matcher.ScoreMatch(L"short", &positions), 0);
    }
}

TEST_F(FuzzyMatcherTest, SeparatorBonus) {
    // Directory separator bonus
    {
        FuzzyMatcher matcher(L"f");
        std::vector<size_t> positions;
        int scoreSep = matcher.ScoreMatch(L"test\\file", &positions);
        int scoreNormal = matcher.ScoreMatch(L"testfile", &positions);
        EXPECT_GT(scoreSep, scoreNormal);
    }

    // Underscore separator bonus
    {
        FuzzyMatcher matcher(L"t");
        std::vector<size_t> positions;
        int scoreSep = matcher.ScoreMatch(L"some_test", &positions);
        int scoreNormal = matcher.ScoreMatch(L"sometest", &positions);
        EXPECT_GT(scoreSep, scoreNormal);
    }
}

TEST_F(FuzzyMatcherTest, ConsecutiveMatches) {
    FuzzyMatcher matcher(L"abc");
    std::vector<size_t> positions;

    int scoreConsecutive = matcher.ScoreMatch(L"abc", &positions);
    int scoreNonConsecutive = matcher.ScoreMatch(L"axbxc", &positions);
    EXPECT_GT(scoreConsecutive, scoreNonConsecutive);
}
