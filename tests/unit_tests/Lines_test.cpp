/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "CompilerUtils.hpp"
#include "Lines.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("calculates number of board lines correctly") {

  SUBCASE("dimensions of 1") {
    Lines lines{1};
    CHECK_EQ(lines.get_max_lines(), 4);
  }

  SUBCASE("dimensions of 2") {
    Lines lines{2};
    CHECK_EQ(lines.get_max_lines(), 12);
  }

  SUBCASE("dimensions of 3") {
    Lines lines{3};
    CHECK_EQ(lines.get_max_lines(), 24);
  }

  SUBCASE("dimensions of 4") {
    Lines lines{4};
    CHECK_EQ(lines.get_max_lines(), 40);
  }

  SUBCASE("copied dimensions of 4") {
    Lines lines_to_copy{4};
    MARK_AS_USED(lines_to_copy);
    Lines lines{ lines_to_copy };
    CHECK_EQ(lines.get_max_lines(), 40);
  }

}

TEST_CASE("all lines unmarked") {

  Lines lines{4};

  SUBCASE("is_marked()") {
    for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
      CHECK_FALSE(lines.is_marked(i));
  }

  SUBCASE("not_marked()") {
    for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
      CHECK_UNARY(lines.not_marked(i));
  }

  SUBCASE("all_marked()") {
    CHECK_FALSE(lines.all_marked());
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 780 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lines.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("all lines marked") {

  Lines lines{4};
  for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
    lines.mark(i);

  SUBCASE("is_marked()") {
    for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
      CHECK_UNARY(lines.is_marked(i));
  }

  SUBCASE("not_marked()") {
    for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
      CHECK_FALSE(lines.not_marked(i));
  }

  SUBCASE("all_marked()") {
    CHECK_UNARY(lines.all_marked());
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lines.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("some lines marked") {

  Lines lines{4};
  lines.mark(0);
  lines.mark(1);
  lines.mark(2);

  SUBCASE("is_marked()") {
    CHECK_UNARY(lines.is_marked(0));
    CHECK_UNARY(lines.is_marked(1));
    CHECK_UNARY(lines.is_marked(2));
    for (std::size_t i = 3; i < lines.get_max_lines(); ++i)
      CHECK_FALSE(lines.is_marked(i));
  }

  SUBCASE("not_marked()") {
    CHECK_FALSE(lines.not_marked(0));
    CHECK_FALSE(lines.not_marked(1));
    CHECK_FALSE(lines.not_marked(2));
    for (std::size_t i = 3; i < lines.get_max_lines(); ++i)
      CHECK_UNARY(lines.not_marked(i));
  }

  SUBCASE("all_marked()") {
    CHECK_FALSE(lines.all_marked());
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 777 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lines.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("copied lines, some lines marked") {

  Lines lines_to_copy{4};
  lines_to_copy.mark(0);
  lines_to_copy.mark(1);
  lines_to_copy.mark(2);
  Lines lines{ lines_to_copy };
  lines_to_copy.mark(3);

  SUBCASE("is_marked()") {
    CHECK_UNARY(lines.is_marked(0));
    CHECK_UNARY(lines.is_marked(1));
    CHECK_UNARY(lines.is_marked(2));
    for (std::size_t i = 3; i < lines.get_max_lines(); ++i)
      CHECK_FALSE(lines.is_marked(i));
  }

  SUBCASE("not_marked()") {
    CHECK_FALSE(lines.not_marked(0));
    CHECK_FALSE(lines.not_marked(1));
    CHECK_FALSE(lines.not_marked(2));
    for (std::size_t i = 3; i < lines.get_max_lines(); ++i)
      CHECK_UNARY(lines.not_marked(i));
  }

  SUBCASE("all_marked()") {
    CHECK_FALSE(lines.all_marked());
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 777 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (std::size_t line_num) { sum += line_num; };
    lines.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("get_unmarked_lines()") {

  Lines lines{2};

  SUBCASE("no lines marked") {
    const std::set<std::size_t>& ul{ lines.get_unmarked_lines() };
    CHECK_EQ(ul.size(), 12);
  }

  SUBCASE("all lines marked") {
    for (std::size_t i = 0; i < lines.get_max_lines(); ++i)
      lines.mark(i);
    const std::set<std::size_t>& ul{ lines.get_unmarked_lines() };
    CHECK_UNARY(ul.empty());
  }

  SUBCASE("all but one line marked") {
    for (std::size_t i = 0; i < lines.get_max_lines() - 1; ++i)
      lines.mark(i);
    const std::set<std::size_t>& ul{ lines.get_unmarked_lines() };
    CHECK_EQ(ul.size(), 1);
    CHECK_EQ(ul.count(lines.get_max_lines() - 1 ), 1);
  }

}

