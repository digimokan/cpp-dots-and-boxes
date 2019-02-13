/*******************************************************************************
module:   TerminalMoveInput
author:   digimokan
date:     13 FEB 2019
purpose:  for current board, collect move input (line num to mark) from terminal
*******************************************************************************/

#ifndef TERMINAL_MOVE_INPUT_HPP
#define TERMINAL_MOVE_INPUT_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MoveInputIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class TerminalMoveInput : public MoveInputIface {

public:

  // constructors
  TerminalMoveInput () = default;

  // destructor
  ~TerminalMoveInput () override = default;

  // operators
  TerminalMoveInput (const TerminalMoveInput& in) = default;
  TerminalMoveInput& operator= (const TerminalMoveInput& rh) = default;
  TerminalMoveInput (TerminalMoveInput&& in) = default;
  TerminalMoveInput& operator= (TerminalMoveInput&& rh) = default;

  // base / derived methods
  std::size_t get_line_to_mark (const std::shared_ptr<SearchNodeIface>& node) final;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // TERMINAL_MOVE_INPUT_HPP

