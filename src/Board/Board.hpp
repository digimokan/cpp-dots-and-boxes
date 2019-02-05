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
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"

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
  std::size_t get_num_lines () const;

private:

  // fields
  std::vector<bool> lines;
  BoxMarks box_marks;

  // helper methods
  std::size_t calc_num_lines (std::size_t dimensions) const;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

