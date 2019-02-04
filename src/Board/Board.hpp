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
  Board& operator= (const Board& rh) = delete;
  Board (Board&& in) = default;
  Board& operator= (Board&& rh) = delete;

  // specialized methods
  std::size_t get_dimensions () const;
  std::size_t get_num_lines () const;

private:

  // fields
  const std::size_t dimensions;
  std::vector<bool> lines;

  // helper methods
  std::size_t calc_num_lines (std::size_t dimensions) const;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

