//#include <gtest/gtest.h>
#include <vector>
#include <tuple>
#include <iostream>

//#include "data_handler.h"
//#include "print.h"

using namespace std::literals;

//std::vector<std::vector<std::string>> ReadInput(std::istream& in);

//TEST(ReadData, CurrentRead) {
//  std::stringstream in;
//  in << "0.0.0.0\\tf\\td\\n"s  << "1.2.1.1\\tf\\td\\n"s  << "1.2.1.3\\tf\\td\\n"s;
//  const std::vector<std::vector<std::string>> check = {{"0.0.0.0"s, "f"s, "d"s },
//                                                         {"1.2.1.1"s, "f"s, "d"s },
//                                                         {"1.2.1.3"s, "f"s, "d"s }};
//  // TODO что надо написать в CmakeLists(как я пологаю) что бы в test.cpp при линковке была видна функция из main.cpp?
//  //const std::vector<std::vector<std::string>> var = ReadInput(in);
//  //ASSERT_EQ(var, check);
//}

//TEST(SelectIp, TestReversResult) {
//    const std::vector<std::vector<std::string>> v = {{"0.0.0.0"s, "f"s, "d"s },
//                                                     {"1.2.1.1"s, "f"s, "d"s },
//                                                     {"1.2.1.3"s, "f"s, "d"s }};
//  std::vector<std::tuple<int, int, int, int>> check = {{1, 2, 1, 3}, {1, 2, 1, 1}, {0, 0, 0, 0}};
//  std::vector<std::tuple<int, int, int, int>> var = SelectIp(v);
//  ASSERT_EQ(var, check);
//}

//TEST(ApplyFilter, OneValue) {
//  std::vector<std::tuple<int, int, int, int>> v = {{9, 8, 7, 6}, {8, 8, 7, 6}, {6, 8, 7, 6}};
//  auto var = ApplyFilter<decltype(v.begin()), 0>({v.begin(), v.end()}, 8);
//  auto check = std::make_pair(++v.begin(), std::next(v.begin(), 2));
//  ASSERT_EQ(var, check);
//}

//TEST(ApplyFilter, TwoValue) {
//  std::vector<std::tuple<int, int, int, int>> v = {{9, 8, 7, 6}, {9, 8, 7, 5}, {6, 8, 7, 6}};
//  auto var = ApplyFilter<decltype(v.begin()), 3>( ApplyFilter<decltype(v.begin()), 0>({v.begin(), v.end()}, 9), 6);
//  auto check = std::make_pair(v.begin(), std::next(v.begin(), 1));
//  ASSERT_EQ(var, check);
//}

//TEST(ApplyFilter, Dist) {
//  std::vector<std::tuple<int, int, int, int>> v = {{9, 8, 7, 6}, {9, 8, 7, 5}, {6, 8, 7, 6}};
//  auto var = ApplyFilter<decltype(v.begin()), 0>({v.begin(), v.end()}, 9);
//  auto check = std::make_pair(v.begin(), std::next(v.begin(), 2));
//  ASSERT_EQ(var, check);
//}

//TEST(PrintAllValue, FindAllVal) {
//  std::vector<std::tuple<int, int, int, int>> v = {{9, 8, 7, 6}, {9, 8, 7, 5}, {6, 8, 7, 6}};
//  std::stringstream var;
//  PrintAllValue(v, 5, std::make_index_sequence<4>(), var);
//  std::string check = "9.8.7.5\n"s;
//  ASSERT_EQ(var.str(), check);
//}

//int main(int argc, char **argv)
//{
//  ::testing::InitGoogleTest(&argc, argv);

//  return RUN_ALL_TESTS();
//}
