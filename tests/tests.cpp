#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include "data_handler.h"

TEST(TestFilter, Filter1) {
  std::vector<std::tuple<int, int, int, int>> v = {{9, 8, 7, 6}, {8, 8, 7, 6}, {6, 8, 7, 6}};
  auto var = ApplyFilter<decltype(v.begin()), 0>({v.begin(), v.end()}, 8);
  auto res = std::make_pair(++v.begin(), std::next(v.begin(), 2));
  ASSERT_EQ(var, res);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
