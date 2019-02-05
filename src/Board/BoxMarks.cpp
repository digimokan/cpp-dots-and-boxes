/*******************************************************************************
module:   BoxMarks
author:   digimokan
date:     04 FEB 2019
purpose:  map of box_num -> marking_player
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cassert>
#include <cstddef>
#include <numeric>
#include <unordered_map>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"
#include "Player.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

BoxMarks::BoxMarks (std::size_t board_dimensions) {
  for (std::size_t i = 0; i < (board_dimensions * board_dimensions); ++i)
    this->unmarked_boxnums.insert(this->unmarked_boxnums.end(), i);
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

bool BoxMarks::is_marked (std::size_t box_num) const {
  return (this->marks.count(box_num) != 0);
}

bool BoxMarks::not_marked (std::size_t box_num) const {
  return (! this->is_marked(box_num));
}

void BoxMarks::mark (std::size_t box_num, Player player) {
  assert(! this->unmarked_boxnums.empty());
  assert(this->marks.count(box_num) == 0);
  assert(this->unmarked_boxnums.count(box_num) == 1);
  assert(this->marked_boxnums.count(box_num) == 0);
  this->marks.insert(std::make_pair(box_num, player));
  this->unmarked_boxnums.erase(box_num);
  this->marked_boxnums.insert(box_num);
}

std::size_t BoxMarks::get_num_unmarked () const {
  return this->unmarked_boxnums.size();
}

bool BoxMarks::all_marked () const {
  return this->unmarked_boxnums.empty();
}

