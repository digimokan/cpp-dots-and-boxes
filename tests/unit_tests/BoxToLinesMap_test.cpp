/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxToLinesMap.hpp"
#include "Lines.hpp"

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

TEST_CASE("all_lines_marked(box_num, lines)") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  BoxToLinesMap blmap{ dimensions };

  SUBCASE("no boxes with any marked lines") {
    Lines lines{ dimensions };
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_FALSE(blmap.all_lines_marked(i, lines));
  }

  SUBCASE("all boxes have all lines marked") {
    Lines lines{ dimensions };
    for (std::size_t i{0}; i < lines.get_max_lines(); ++i)
      lines.mark(i);
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_UNARY(blmap.all_lines_marked(i, lines));
  }

  SUBCASE("one box with all lines marked") {
    Lines lines{ dimensions };
    blmap.for_each_line_num(0, [&lines] (const auto line_num) { lines.mark(line_num); });
    CHECK_UNARY(blmap.all_lines_marked(0, lines));
    for (std::size_t i{1}; i < num_boxes; ++i)
      CHECK_FALSE(blmap.all_lines_marked(i, lines));
  }

  SUBCASE("three boxes with all lines marked") {
    Lines lines{ dimensions };
    blmap.for_each_line_num(0, [&lines] (const auto line_num) { if (lines.not_marked(line_num)) lines.mark(line_num); });
    blmap.for_each_line_num(1, [&lines] (const auto line_num) { if (lines.not_marked(line_num)) lines.mark(line_num); });
    blmap.for_each_line_num(2, [&lines] (const auto line_num) { if (lines.not_marked(line_num)) lines.mark(line_num); });
    CHECK_UNARY(blmap.all_lines_marked(0, lines));
    CHECK_UNARY(blmap.all_lines_marked(1, lines));
    CHECK_UNARY(blmap.all_lines_marked(2, lines));
    for (std::size_t i{3}; i < num_boxes; ++i)
      CHECK_FALSE(blmap.all_lines_marked(i, lines));
  }

  SUBCASE("one box with some lines marked") {
    Lines lines{ dimensions };
    lines.mark(0);
    lines.mark(3);
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_FALSE(blmap.all_lines_marked(i, lines));
  }

  SUBCASE("three boxes with some lines marked") {
    Lines lines{ dimensions };
    lines.mark(0);
    lines.mark(1);
    lines.mark(2);
    lines.mark(4);
    lines.mark(5);
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_FALSE(blmap.all_lines_marked(i, lines));
  }

}

