/*******************************************************************************
module:   LineToBoxesMap
author:   digimokan
date:     06 FEB 2019
purpose:  map a line number to multiple box numbers
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

#ifndef LINE_TO_BOXES_MAP_HPP
#define LINE_TO_BOXES_MAP_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>
#include <set>
#include <unordered_map>

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class LineToBoxesMap {

public:

  // constructors
  LineToBoxesMap () = delete;
  explicit LineToBoxesMap (std::size_t board_dimensions);

  // destructor
  ~LineToBoxesMap () = default;

  // operators
  LineToBoxesMap (const LineToBoxesMap& in) = default;
  LineToBoxesMap& operator= (const LineToBoxesMap& rh) = default;
  LineToBoxesMap (LineToBoxesMap&& in) = default;
  LineToBoxesMap& operator= (LineToBoxesMap&& rh) = default;

  // specialized methods
  void for_each_box_num (std::size_t line_num, const std::function<void(std::size_t box_num)>& act_on_box) const;

private:

  // helper methods
  void init_map (std::size_t board_dimensions);
  void init_line_sets (std::size_t board_dimensions);

  // fields
  std::unordered_map<std::size_t, std::set<std::size_t>> lbmap;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // LINE_TO_BOXES_MAP_HPP

