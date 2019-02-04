/*******************************************************************************
module:   Board
author:   digimokan
date:     02 FEB 2019
purpose:  a dots and boxes board
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "BoxMarks.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

Board::Board (std::size_t dimensions)
  : dimensions{dimensions},
    lines(this->calc_num_lines(dimensions), false),
    box_marks{ dimensions }
{ }

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::size_t Board::get_dimensions () const {
  return this->dimensions;
}

std::size_t Board::get_num_lines () const {
  return this->lines.size();
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

std::size_t Board::calc_num_lines (std::size_t dimensions) const {
  return ( (2 * dimensions) * (dimensions + 1) );
}

