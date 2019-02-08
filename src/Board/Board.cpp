/*******************************************************************************
module:   Board
author:   digimokan
date:     02 FEB 2019
purpose:  a dots and boxes board
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cassert>
#include <cstddef>
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "BoxMarks.hpp"
#include "BoxToLinesMap.hpp"
#include "LineToBoxesMap.hpp"
#include "Player.hpp"

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

std::size_t Board::get_max_lines () const {
  return this->lines.get_max_lines();
}

void Board::mark_line (Player player, std::size_t line_num) {
  this->lines.mark(line_num);
  auto mk{ [this, player] (const auto box_num) { this->check_and_mark_box(box_num, player); } };
  this->lbmap->for_each_box_num(line_num, mk);
}

bool Board::is_line_marked (std::size_t line_num) const {
  return this->lines.is_marked(line_num);
}

void Board::for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const {
  this->lines.for_each_unmarked_line_num(act_on_line_num);
}

bool Board::is_box_marked (std::size_t box_num) const {
  return this->box_marks.is_marked(box_num);
}

Player Board::get_box_mark (std::size_t box_num) const {
  assert(this->is_box_marked(box_num));
  return this->box_marks.get_mark(box_num);
}

bool Board::is_completed () const {
  return this->lines.all_marked();
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void Board::check_and_mark_box (std::size_t box_num, Player player) {
  if (this->blmap->all_lines_marked(box_num, this->lines))
    this->box_marks.mark(box_num, player);
}

