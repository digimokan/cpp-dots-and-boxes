/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("num lines") {

  SUBCASE("1 x 1 board") {
    Board board{1};
    CHECK_EQ(board.get_num_lines(), 4);
  }

  SUBCASE("2 x 2 board") {
    Board board{2};
    CHECK_EQ(board.get_num_lines(), 12);
  }

  SUBCASE("3 x 3 board") {
    Board board{3};
    CHECK_EQ(board.get_num_lines(), 24);
  }

  SUBCASE("4 x 4 board") {
    Board board{4};
    CHECK_EQ(board.get_num_lines(), 40);
  }

}

