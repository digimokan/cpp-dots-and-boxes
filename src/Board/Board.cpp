/*******************************************************************************
module:   Board
author:   digimokan
date:     02 FEB 2019
purpose:  a dots and boxes board
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <sstream>
#include <string>

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
    lbmap{ std::make_shared<LineToBoxesMap>(dimensions) } {
  assert(dimensions <= this->get_max_dimensions());
}

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

const std::set<std::size_t>& Board::get_unmarked_lines () const {
  return this->lines.get_unmarked_lines();
}

bool Board::is_box_marked (std::size_t box_num) const {
  return this->box_marks.is_marked(box_num);
}

Player Board::get_box_mark (std::size_t box_num) const {
  assert(this->is_box_marked(box_num));
  return this->box_marks.get_mark(box_num);
}

void Board::for_each_player_boxmark (Player player,
    const std::function<void(std::size_t box_num)>& act_on_box_num) const {
  this->box_marks.for_each_player_boxmark(player, act_on_box_num);
}

bool Board::is_completed () const {
  return this->lines.all_marked();
}

std::size_t Board::get_line_num (const std::string& row_col_code) const {
  std::string uc{};
  uc.resize(row_col_code.size());
  std::transform(row_col_code.cbegin(), row_col_code.cend(), uc.begin(), ::toupper);
  std::size_t row_index{ this->get_label_index(uc.at(0)) };
  std::size_t col_index{ this->get_label_index(uc.at(1)) };
  const std::size_t dim{ this->get_board_dimensions() };
  return ( (row_index * dim) + (row_index / 2) + (col_index / 2) );
}

bool Board::is_row_col_code_valid (const std::string& row_col_code) const {
  const std::size_t dim{ this->get_board_dimensions() };
  std::string uc{};
  uc.resize(row_col_code.size());
  std::transform(row_col_code.cbegin(), row_col_code.cend(), uc.begin(), ::toupper);
  if (uc.size() != 2)
    return false;
  if (this->get_hdr_labels().find(uc.at(0)) == std::string::npos)
    return false;
  if (this->get_hdr_labels().find(uc.at(1)) == std::string::npos)
    return false;
  const std::size_t row_pos{ this->get_hdr_labels().find(uc.at(0)) };
  const std::size_t col_pos{ this->get_hdr_labels().find(uc.at(1)) };
  if (row_pos > (dim * 2))
    return false;
  if (col_pos > (dim * 2))
    return false;
  if ((row_pos % 2) == (col_pos % 2))
    return false;
  return true;
}

std::string Board::get_row_col_code (std::size_t line_num) const {
  std::string code{};
  return (code + this->get_row_code(line_num) + this->get_col_code(line_num));
}

/*******************************************************************************
* FRIEND CLASS METHODS
*******************************************************************************/

std::ostream& operator<< (std::ostream& os, const Board& board) {
  const std::size_t dim{ board.get_board_dimensions() };
  os << board.row_label_string();
  os << board.first_box_row_string();
  for (std::size_t box_row{0}; box_row < dim; ++box_row)
    os << board.box_row_string(box_row);
  return os;
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void Board::check_and_mark_box (std::size_t box_num, Player player) {
  if (this->blmap->all_lines_marked(box_num, this->lines))
    this->box_marks.mark(box_num, player);
}

std::size_t Board::get_board_dimensions () const {
  return this->box_marks.get_board_dimensions();
}

std::size_t Board::get_num_boxes () const {
  return this->box_marks.get_num_boxes();
}

std::string Board::get_top_line (std::size_t box_num) const {
  if (this->lines.is_marked(this->blmap->get_top_line_num(box_num)))
    return u8"―";
  return u8" ";
}

std::string Board::get_bottom_line (std::size_t box_num) const {
  if (this->lines.is_marked(this->blmap->get_bottom_line_num(box_num)))
    return u8"―";
  return u8" ";
}

std::string Board::get_left_line (std::size_t box_num) const {
  if (this->lines.is_marked(this->blmap->get_left_line_num(box_num)))
    return u8"|";
  return u8" ";
}

std::string Board::get_right_line (std::size_t box_num) const {
  if (this->lines.is_marked(this->blmap->get_right_line_num(box_num)))
    return u8"|";
  return u8" ";
}

std::string Board::get_box_fill (std::size_t box_num) const {
  std::stringstream out_fill;
  if (this->box_marks.is_marked(box_num))
    out_fill << this->box_marks.get_mark(box_num);
  else
    out_fill << u8" ";
  return out_fill.str();
}

std::string Board::row_label_string () const {
  const std::size_t dim{ this->get_board_dimensions() };
  const std::size_t max_col_index{ (2 * dim) + 1 };
  std::string out_string{};
  out_string.append(u8" ");
  for (std::size_t col_index{0}; col_index < max_col_index; ++col_index) {
    out_string.append(u8" ");
    out_string.push_back(this->get_hdr_labels().at(col_index));
  }
  return out_string;
}

std::string Board::first_box_row_string () const {
  const std::size_t dim{ this->get_board_dimensions() };
  std::string out_string{};
  out_string.append(u8"\n");
  out_string.append(u8"A");
  out_string.append(u8" ");
  out_string.append(u8"·");
  for (std::size_t i{0}; i < dim; ++i) {
    out_string.append(u8" ");
    out_string.append(this->get_top_line(i));
    out_string.append(u8" ");
    out_string.append(u8"·");
  }
  return out_string;
}

std::string Board::box_row_string (std::size_t box_row_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  std::string out_string{};
  out_string.append(u8"\n");
  out_string.push_back(this->get_hdr_labels().at(((box_row_num + 1) * 2) - 1));
  out_string.append(u8" ");
  out_string.append(this->get_left_line(box_row_num * dim));
  for (std::size_t i{0}; i < dim; ++i) {
    const std::size_t box_num{ (box_row_num * dim) + i };
    out_string.append(u8" ");
    out_string.append(this->get_box_fill(box_num));
    out_string.append(u8" ");
    out_string.append(this->get_right_line(box_num));
  }
  out_string.append(u8"\n");
  out_string.push_back(this->get_hdr_labels().at((box_row_num + 1) * 2));
  out_string.append(u8" ");
  out_string.append(u8"·");
  for (std::size_t i{0}; i < dim; ++i) {
    const std::size_t box_num{ (box_row_num * dim) + i };
    out_string.append(u8" ");
    out_string.append(this->get_bottom_line(box_num));
    out_string.append(u8" ");
    out_string.append(u8"·");
  }
  return out_string;
}

const std::string& Board::get_hdr_labels () const {
  static const std::string labels{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
  return labels;
}

std::size_t Board::get_label_index (char code) const {
  const std::size_t code_pos{ this->get_hdr_labels().find(code) };
  assert(code_pos != std::string::npos);
  return code_pos;
}

char Board::get_row_code (std::size_t line_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  std::size_t row_index{ 0 };
  std::size_t line_counter{ 0 };
  while(true) {
    line_counter += dim;
    if (line_counter >= (line_num + 1))
      break;
    row_index++;
    line_counter += (dim + 1);
    if (line_counter >= (line_num + 1))
      break;
    row_index++;
  }
  return this->get_hdr_labels().at(row_index);
}

char Board::get_col_code (std::size_t line_num) const {
  const std::size_t dim{ this->get_board_dimensions() };
  std::size_t row_index{ this->get_hdr_labels().find( this->get_row_code(line_num) ) };
  const std::size_t row_base{ (row_index * dim) + (row_index / 2) };
  const std::size_t col_base{ static_cast<size_t>(((row_index % 2) == 0) ? 1 : 0) };
  const std::size_t col_counter{ line_num - row_base };
  const std::size_t col_index{ col_base + (col_counter * 2) };
  return this->get_hdr_labels().at(col_index);
}

