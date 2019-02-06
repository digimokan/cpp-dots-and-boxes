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

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>
#include <set>
#include <unordered_map>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxToLinesMap.hpp"
#include "LineToBoxesMap.hpp"
#include "Lines.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

LineToBoxesMap::LineToBoxesMap (std::size_t board_dimensions) {
  this->init_map(board_dimensions);
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void LineToBoxesMap::for_each_box_num (std::size_t line_num,
    const std::function<void(std::size_t box_num)>& act_on_box) const {
  for (const auto& box_num : this->lbmap.at(line_num))
    act_on_box(box_num);
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void LineToBoxesMap::init_map (std::size_t board_dimensions) {
  this->init_line_sets(board_dimensions);
  const std::size_t num_boxes{ board_dimensions * board_dimensions };
  for (std::size_t box_num = 0; box_num < num_boxes; ++box_num) {
    const auto add_mapping = [this, box_num] (std::size_t line_num) { this->lbmap.at(line_num).emplace(box_num); };
    const BoxToLinesMap blmap{ board_dimensions };
    blmap.for_each_line_num(box_num, add_mapping);
  }
}

void LineToBoxesMap::init_line_sets (std::size_t board_dimensions) {
  const std::size_t num_lines{ Lines{board_dimensions}.get_num_lines() };
  for (std::size_t line_num = 0; line_num < num_lines; ++line_num) {
    std::set<size_t> empty_set{};
    this->lbmap.emplace(line_num, empty_set);
  }
}

