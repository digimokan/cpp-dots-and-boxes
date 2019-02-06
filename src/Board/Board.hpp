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

private:

  // fields
  Lines lines;
  BoxMarks box_marks;
  std::shared_ptr<const BoxToLinesMap> blmap;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOARD_HPP

