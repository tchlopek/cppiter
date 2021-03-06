#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

#include <iter.hpp>

#include "matcher.hpp"

using namespace testing;
using cppiter::iter;

class MapRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5 };
};

TEST_F(MapRangeForRandomAccessTest, NumbersAreSquared) {
    ASSERT_THAT(iter(v).map([](int v){ return v * v; }), ElementsAre(1, 4, 9, 16, 25));
}

TEST_F(MapRangeForRandomAccessTest, EmptyTest) {
    ASSERT_THAT(iter(std::vector<int>{}).map([](int v){ return v * v; }), utest::IsEmpty());
}
