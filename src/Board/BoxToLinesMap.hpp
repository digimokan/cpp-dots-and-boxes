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

#ifndef BOX_TO_LINES_MAP_HPP
#define BOX_TO_LINES_MAP_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class BoxToLinesMap {

public:

  // constructors
  BoxToLinesMap () = delete;
  explicit BoxToLinesMap (std::size_t board_dimensions);

  // destructor
  ~BoxToLinesMap () = default;

  // operators
  BoxToLinesMap (const BoxToLinesMap& in) = default;
  BoxToLinesMap& operator= (const BoxToLinesMap& rh) = default;
  BoxToLinesMap (BoxToLinesMap&& in) = default;
  BoxToLinesMap& operator= (BoxToLinesMap&& rh) = default;

  // specialized methods
  std::size_t get_top_line_num (std::size_t box_num) const;
  std::size_t get_bottom_line_num (std::size_t box_num) const;
  std::size_t get_left_line_num (std::size_t box_num) const;
  std::size_t get_right_line_num (std::size_t box_num) const;
  void for_each_line_num (std::size_t box_num, const std::function<void(std::size_t line_num)>& act_on_line) const;

private:

  // helper methods
  std::size_t get_board_dimensions () const;

  // fields
  std::size_t board_dimensions;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOX_TO_LINES_MAP_HPP

