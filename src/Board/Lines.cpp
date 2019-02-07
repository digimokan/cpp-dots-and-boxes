/*******************************************************************************
module:   Lines
author:   digimokan
date:     04 FEB 2019
purpose:  data structure containing the unique lines of a dots and boxes board
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Lines.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

Lines::Lines (std::size_t dimensions)
  : lines(this->calc_num_lines(dimensions), false)
{ }

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void Lines::mark (std::size_t line_num) {
  assert(! this->lines[line_num]);
  this->lines[line_num] = true;
}

bool Lines::is_marked (std::size_t line_num) const {
  return this->lines[line_num];
}

bool Lines::not_marked (std::size_t line_num) const {
  return (! this->is_marked(line_num));
}

bool Lines::all_marked () const {
  return std::all_of(this->lines.cbegin(), this->lines.cend(), [] (auto line) { return line; });
}

std::size_t Lines::get_max_lines () const {
  return this->lines.size();
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

std::size_t Lines::calc_num_lines (std::size_t dimensions) const {
  return ( (2 * dimensions) * (dimensions + 1) );
}

