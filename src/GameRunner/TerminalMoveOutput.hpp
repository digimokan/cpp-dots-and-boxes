/*******************************************************************************
module:   TerminalMoveOutput
author:   digimokan
date:     13 FEB 2019
purpose:  output a SearchNode's current board, scores, etc to the terminal
*******************************************************************************/

#ifndef TERMINAL_MOVE_OUTPUT_HPP
#define TERMINAL_MOVE_OUTPUT_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MoveOutputIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class TerminalMoveOutput : public MoveOutputIface {

public:

  // constructors
  TerminalMoveOutput () = default;

  // destructor
  ~TerminalMoveOutput () override = default;

  // operators
  TerminalMoveOutput (const TerminalMoveOutput& in) = default;
  TerminalMoveOutput& operator= (const TerminalMoveOutput& rh) = default;
  TerminalMoveOutput (TerminalMoveOutput&& in) = default;
  TerminalMoveOutput& operator= (TerminalMoveOutput&& rh) = default;

  // base / derived methods
  void send (std::shared_ptr<SearchNodeIface> node) final;

private:

  std::string last_line_marked (const std::shared_ptr<SearchNodeIface>& node) const;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // TERMINAL_MOVE_OUTPUT_HPP

