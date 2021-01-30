#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>
#include <forward_list>

#include <filter_range.hpp>

using namespace testing;

namespace {

bool odd(int e) {
    return e % 2 == 1;
}

}

class FilterRangeForRandomAccessTest : public Test {
public:
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
};

TEST_F(FilterRangeForRandomAccessTest, FilteredNumbersAreOdd) {
      ASSERT_THAT(filter(v, odd), ElementsAre(1, 3, 5, 7));
}