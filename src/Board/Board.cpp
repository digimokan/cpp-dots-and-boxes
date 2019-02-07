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
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "BoxMarks.hpp"
#include "BoxToLinesMap.hpp"
#include "LineToBoxesMap.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

Board::Board (std::size_t dimensions)
  : lines{ dimensions },
    box_marks{ dimensions },
    blmap{ std::make_shared<BoxToLinesMap>(dimensions) },
    lbmap{ std::make_shared<LineToBoxesMap>(dimensions) }
{ }

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void Board::for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const {
  this->lines.for_each_unmarked_line_num(act_on_line_num);
}

bool Board::is_completed () const {
  return this->lines.all_marked();
}

