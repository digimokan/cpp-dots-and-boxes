/*******************************************************************************
module:   Board
author:   digimokan
date:     02 FEB 2019
purpose:  a dots and boxes board
*******************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"
#include "Lines.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class BoxToLinesMap;
class LineToBoxesMap;
enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class Board {

public:

  // constructors
  Board () = delete;
  explicit Board (std::size_t dimensions);

  // destructor
  ~Board () = default;

  // operators
  Board (const Board& in) = default;
  Board& operator= (const Board& rh) = default;
  Board (Board&& in) = default;
  Board& operator= (Board&& rh) = default;

  // specialized methods
  constexpr std::size_t get_max_dimensions () { return 10; }
  std::size_t get_max_lines () const;
  void mark_line (Player player, std::size_t line_num);
  bool is_line_marked (std::size_t line_num) const;
  void for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const;
  bool is_box_marked (std::size_t box_num) const;
  Player get_box_mark (std::size_t box_num) const;
  void for_each_player_boxmark (Player player, const std::function<void(std::size_t box_num)>& act_on_box_num) const;
  bool is_completed () const;
  std::size_t get_line_num (const std::string& row_col_code) const;
  bool is_row_col_code_valid (const std::string& row_col_code) const;

  // friend class methods
  friend std::ostream& operator<< (std::ostream& os, const Board& board);

private:

  // fields
  Lines lines;
  BoxMarks box_marks;
  std::shared_ptr<const BoxToLinesMap> blmap;
  std::shared_ptr<const LineToBoxesMap> lbmap;

  // helper methods
  void check_and_mark_box (std::size_t box_num, Player player);
  std::size_t get_board_dimensions () const;
  std::size_t get_num_boxes () const;
  std::string get_top_line (std::size_t box_num) const;
  std::string get_bottom_line (std::size_t box_num) const;
  std::string get_left_line (std::size_t box_num) const;
  std::string get_right_line (std::size_t box_num) const;
  std::string get_box_fill (std::size_t box_num) const;
  std::string row_label_string () const;
  std::string first_box_row_string () const;
  std::string box_row_string (std::size_t box_row_num) const;
  const std::string& get_hdr_labels () const;
  std::size_t get_label_index (char code) const;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

