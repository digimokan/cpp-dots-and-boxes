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
#include <memory>

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
  std::size_t get_max_lines () const;
  void mark_line (Player player, std::size_t line_num);
  bool is_line_marked (std::size_t line_num) const;
  void for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const;
  bool is_box_marked (std::size_t box_num) const;
  Player get_box_mark (std::size_t box_num) const;
  void for_each_player_boxmark (Player player, const std::function<void(std::size_t box_num)>& act_on_box_num) const;
  bool is_completed () const;

private:

  // fields
  Lines lines;
  BoxMarks box_marks;
  std::shared_ptr<const BoxToLinesMap> blmap;
  std::shared_ptr<const LineToBoxesMap> lbmap;

  // helper methods
  void check_and_mark_box (std::size_t box_num, Player player);

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

