/*******************************************************************************
module:   BoxToLinesMap
author:   digimokan
date:     05 FEB 2019
purpose:  map a box number to multiple line numbers
              BOX NUMBERING:          LINE NUMBERING:
          ·―――――·―――――·―――――·      ·――0――·――1――·――2――·
          |     |     |     |      |     |     |     |
          |  0  |  1  |  2  |      3     4     5     6
          |     |     |     |      |     |     |     |
          ·―――――·―――――·―――――·      ·――7――·――8――·――9――·
          |     |     |     |      |     |     |     |
          |  3  |  4  |  5  |      10    11    12    13
          |     |     |     |      |     |     |     |
          ·―――――·―――――·―――――·      ·―14――·―15――·―16――·
          |     |     |     |      |     |     |     |
          |  6  |  7  |  8  |      17    18    19    20
          |     |     |     |      |     |     |     |
          ·―――――·―――――·―――――·      ·―21――·―22――·―23――·
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxToLinesMap.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

BoxToLinesMap::BoxToLinesMap (std::size_t board_dimensions)
  : board_dimensions{board_dimensions}
{ }

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::size_t BoxToLinesMap::get_top_line_num (std::size_t box_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  return (
      ( ((dim * 2) + 1) * (box_num / dim) )
    + ( box_num % dim )
  );
}

std::size_t BoxToLinesMap::get_bottom_line_num (std::size_t box_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  return (
      ( ((dim * 2) + 1) * ((box_num / dim) + 1) )
    + ( box_num % dim )
  );
}

std::size_t BoxToLinesMap::get_left_line_num (std::size_t box_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  return (
      ( ((dim * 2) + 1) * ((box_num / dim) + 1) )
    - ( dim + 1 )
    + ( box_num % dim )
  );
}

std::size_t BoxToLinesMap::get_right_line_num (std::size_t box_num) const {
  return ( this->get_left_line_num(box_num) + 1 );
}

void BoxToLinesMap::for_each_line_num (std::size_t box_num,
    const std::function<void(std::size_t line_num)>& act_on_line) const {
  act_on_line(this->get_top_line_num(box_num));
  act_on_line(this->get_bottom_line_num(box_num));
  act_on_line(this->get_left_line_num(box_num));
  act_on_line(this->get_right_line_num(box_num));
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

std::size_t BoxToLinesMap::get_board_dimensions () const {
  return this->board_dimensions;
}

