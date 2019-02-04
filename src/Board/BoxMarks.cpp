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
#include <unordered_map>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"
#include "Player.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

BoxMarks::BoxMarks (std::size_t board_dimensions)
  : num_unmarked{board_dimensions * board_dimensions}
{ }

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
  assert(this->not_marked(box_num) > 0);
  this->marks.insert(std::make_pair(box_num, player));
  assert(this->num_unmarked > 0);
  this->num_unmarked--;
}

std::size_t BoxMarks::get_num_unmarked () const {
  return this->num_unmarked;
}

bool BoxMarks::all_marked () const {
  return (this->num_unmarked == 0);
}

