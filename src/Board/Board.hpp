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

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class Board {

public:

  // constructors
  Board () = delete;
  explicit Board (std::size_t dimension);

  // destructor
  ~Board () = default;

  // operators
  Board (const Board& in) = default;
  Board& operator= (const Board& rh) = default;
  Board (Board&& in) = default;
  Board& operator= (Board&& rh) = default;

  // specialized methods
  size_t get_dimension () const;

private:

  // fields
  std::size_t dimension;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

