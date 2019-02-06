/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "LineToBoxesMap.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("1 x 1 board") {

  LineToBoxesMap lbmap{ 1 };

  SUBCASE("line 0") {
    constexpr std::size_t line_num{ 0 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 1") {
    constexpr std::size_t line_num{ 1 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 2") {
    constexpr std::size_t line_num{ 2 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 3") {
    constexpr std::size_t line_num{ 3 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("2 x 2 board") {

  LineToBoxesMap lbmap{ 2 };

  SUBCASE("line 0") {
    constexpr std::size_t line_num{ 0 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 1") {
    constexpr std::size_t line_num{ 1 };
    constexpr std::size_t expected_sum{ 1 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 2") {
    constexpr std::size_t line_num{ 2 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 3") {
    constexpr std::size_t line_num{ 3 };
    constexpr std::size_t expected_sum{ 1 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 4") {
    constexpr std::size_t line_num{ 4 };
    constexpr std::size_t expected_sum{ 1 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 5") {
    constexpr std::size_t line_num{ 5 };
    constexpr std::size_t expected_sum{ 2 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 6") {
    constexpr std::size_t line_num{ 6 };
    constexpr std::size_t expected_sum{ 4 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 7") {
    constexpr std::size_t line_num{ 7 };
    constexpr std::size_t expected_sum{ 2 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 8") {
    constexpr std::size_t line_num{ 8 };
    constexpr std::size_t expected_sum{ 5 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 9") {
    constexpr std::size_t line_num{ 9 };
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 10") {
    constexpr std::size_t line_num{ 10 };
    constexpr std::size_t expected_sum{ 2 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 11") {
    constexpr std::size_t line_num{ 11 };
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("3 x 3 board") {

  LineToBoxesMap lbmap{ 3 };

  SUBCASE("line 0") {
    constexpr std::size_t line_num{ 0 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 1") {
    constexpr std::size_t line_num{ 1 };
    constexpr std::size_t expected_sum{ 1 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 2") {
    constexpr std::size_t line_num{ 2 };
    constexpr std::size_t expected_sum{ 2 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 3") {
    constexpr std::size_t line_num{ 3 };
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 4") {
    constexpr std::size_t line_num{ 4 };
    constexpr std::size_t expected_sum{ 1 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 5") {
    constexpr std::size_t line_num{ 5 };
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 6") {
    constexpr std::size_t line_num{ 6 };
    constexpr std::size_t expected_sum{ 2 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 7") {
    constexpr std::size_t line_num{ 7 };
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 8") {
    constexpr std::size_t line_num{ 8 };
    constexpr std::size_t expected_sum{ 5 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 9") {
    constexpr std::size_t line_num{ 9 };
    constexpr std::size_t expected_sum{ 7 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 10") {
    constexpr std::size_t line_num{ 10 };
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 11") {
    constexpr std::size_t line_num{ 11 };
    constexpr std::size_t expected_sum{ 7 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 12") {
    constexpr std::size_t line_num{ 12 };
    constexpr std::size_t expected_sum{ 9 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 13") {
    constexpr std::size_t line_num{ 13 };
    constexpr std::size_t expected_sum{ 5 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 14") {
    constexpr std::size_t line_num{ 14 };
    constexpr std::size_t expected_sum{ 9 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 15") {
    constexpr std::size_t line_num{ 15 };
    constexpr std::size_t expected_sum{ 11 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 16") {
    constexpr std::size_t line_num{ 16 };
    constexpr std::size_t expected_sum{ 13 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 17") {
    constexpr std::size_t line_num{ 17 };
    constexpr std::size_t expected_sum{ 6 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 18") {
    constexpr std::size_t line_num{ 18 };
    constexpr std::size_t expected_sum{ 13 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 19") {
    constexpr std::size_t line_num{ 19 };
    constexpr std::size_t expected_sum{ 15 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 20") {
    constexpr std::size_t line_num{ 20 };
    constexpr std::size_t expected_sum{ 8 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 21") {
    constexpr std::size_t line_num{ 21 };
    constexpr std::size_t expected_sum{ 6 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 22") {
    constexpr std::size_t line_num{ 22 };
    constexpr std::size_t expected_sum{ 7 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("line 23") {
    constexpr std::size_t line_num{ 23 };
    constexpr std::size_t expected_sum{ 8 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lbmap.for_each_box_num(line_num, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

