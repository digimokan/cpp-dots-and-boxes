/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("empty BoxMarks") {

  SUBCASE("1 x 1 Board") {
    constexpr std::size_t dimensions{ 1 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
  }

  SUBCASE("2 x 2 Board") {
    constexpr std::size_t dimensions{ 2 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
  }

  SUBCASE("3 x 3 Board") {
    constexpr std::size_t dimensions{ 3 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
  }

  SUBCASE("copied 3 x 3 Board") {
    constexpr std::size_t dimensions{ 3 };
    BoxMarks box_marks_to_copy{ dimensions };
    BoxMarks box_marks{ box_marks_to_copy };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
  }

}

