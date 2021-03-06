#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

namespace {

bool isValue2Or3(int v) {
    return v == 2 || v == 3;
}

}

class ReplaceRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 4, 2, 3, 4, 5 };
};

TEST_F(ReplaceRangeForRandomAccessTest, ReplacedElementsUsingPredicate) {
    ASSERT_THAT(iter(v).replace(isValue2Or3, 20), ElementsAre(4, 20, 20, 4, 5));
}

TEST_F(ReplaceRangeForRandomAccessTest, ElementsReplacedUsingValueMatcher) {
    ASSERT_THAT(iter(v).replace(4, 7), ElementsAre(7, 2, 3, 7, 5));
}

TEST_F(ReplaceRangeForRandomAccessTest, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).replace(0, 1), utest::IsEmpty());
}
