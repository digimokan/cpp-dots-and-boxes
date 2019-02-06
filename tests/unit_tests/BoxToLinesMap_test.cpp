/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxToLinesMap.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("1 x 1 board") {

  BoxToLinesMap blmap{ 1 };

  SUBCASE("box 0") {
    constexpr std::size_t expected_sum{ 6 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 0 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 0);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 3);
    CHECK_EQ(blmap.get_left_line_num(box_num), 1);
    CHECK_EQ(blmap.get_right_line_num(box_num), 2);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("2 x 2 board") {

  BoxToLinesMap blmap{ 2 };

  SUBCASE("box 0") {
    constexpr std::size_t expected_sum{ 10 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 0 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 0);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 5);
    CHECK_EQ(blmap.get_left_line_num(box_num), 2);
    CHECK_EQ(blmap.get_right_line_num(box_num), 3);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 1") {
    constexpr std::size_t expected_sum{ 14 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 1 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 1);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 6);
    CHECK_EQ(blmap.get_left_line_num(box_num), 3);
    CHECK_EQ(blmap.get_right_line_num(box_num), 4);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 2") {
    constexpr std::size_t expected_sum{ 30 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 2 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 5);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 10);
    CHECK_EQ(blmap.get_left_line_num(box_num), 7);
    CHECK_EQ(blmap.get_right_line_num(box_num), 8);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 3") {
    constexpr std::size_t expected_sum{ 34 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 3 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 6);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 11);
    CHECK_EQ(blmap.get_left_line_num(box_num), 8);
    CHECK_EQ(blmap.get_right_line_num(box_num), 9);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("3 x 3 board") {

  BoxToLinesMap blmap{ 3 };

  SUBCASE("box 0") {
    constexpr std::size_t expected_sum{ 14 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 0 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 0);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 7);
    CHECK_EQ(blmap.get_left_line_num(box_num), 3);
    CHECK_EQ(blmap.get_right_line_num(box_num), 4);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 1") {
    constexpr std::size_t expected_sum{ 18 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 1 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 1);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 8);
    CHECK_EQ(blmap.get_left_line_num(box_num), 4);
    CHECK_EQ(blmap.get_right_line_num(box_num), 5);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 2") {
    constexpr std::size_t expected_sum{ 22 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 2 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 2);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 9);
    CHECK_EQ(blmap.get_left_line_num(box_num), 5);
    CHECK_EQ(blmap.get_right_line_num(box_num), 6);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 3") {
    constexpr std::size_t expected_sum{ 42 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 3 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 7);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 14);
    CHECK_EQ(blmap.get_left_line_num(box_num), 10);
    CHECK_EQ(blmap.get_right_line_num(box_num), 11);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 4") {
    constexpr std::size_t expected_sum{ 46 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 4 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 8);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 15);
    CHECK_EQ(blmap.get_left_line_num(box_num), 11);
    CHECK_EQ(blmap.get_right_line_num(box_num), 12);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 5") {
    constexpr std::size_t expected_sum{ 50 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 5 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 9);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 16);
    CHECK_EQ(blmap.get_left_line_num(box_num), 12);
    CHECK_EQ(blmap.get_right_line_num(box_num), 13);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 6") {
    constexpr std::size_t expected_sum{ 70 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 6 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 14);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 21);
    CHECK_EQ(blmap.get_left_line_num(box_num), 17);
    CHECK_EQ(blmap.get_right_line_num(box_num), 18);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 7") {
    constexpr std::size_t expected_sum{ 74 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 7 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 15);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 22);
    CHECK_EQ(blmap.get_left_line_num(box_num), 18);
    CHECK_EQ(blmap.get_right_line_num(box_num), 19);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("box 8") {
    constexpr std::size_t expected_sum{ 78 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    constexpr std::size_t box_num{ 8 };
    CHECK_EQ(blmap.get_top_line_num(box_num), 16);
    CHECK_EQ(blmap.get_bottom_line_num(box_num), 23);
    CHECK_EQ(blmap.get_left_line_num(box_num), 19);
    CHECK_EQ(blmap.get_right_line_num(box_num), 20);
    blmap.for_each_line_num(box_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

