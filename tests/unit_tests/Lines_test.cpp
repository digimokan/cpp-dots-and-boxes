/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Lines.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("num lines") {

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
    Lines lines{ lines_to_copy };
    CHECK_EQ(lines.get_max_lines(), 40);
  }

}

