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
  : lines(this->calc_num_lines(dimensions), false) {
  this->init_unmarked_lines();
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void Lines::mark (std::size_t line_num) {
  assert(! this->lines[line_num]);
  assert(this->unmarked_lines.count(line_num) == 1);
  this->lines[line_num] = true;
  this->unmarked_lines.erase(line_num);
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

void Lines::for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const {
  for (const auto& line_num : this->unmarked_lines)
    act_on_line_num(line_num);
}

const std::set<std::size_t>& Lines::get_unmarked_lines () const {
  return this->unmarked_lines;
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void Lines::init_unmarked_lines () {
  for (std::size_t i = 0; i < this->get_max_lines(); ++i)
    this->unmarked_lines.emplace(i);
}

std::size_t Lines::calc_num_lines (std::size_t dimensions) const {
  return ( (2 * dimensions) * (dimensions + 1) );
}

