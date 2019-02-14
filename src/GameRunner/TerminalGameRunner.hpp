/*******************************************************************************
module:   TerminalGameRunner
author:   digimokan
date:     13 FEB 2019
purpose:  run a dots and boxes game with terminal input/output
*******************************************************************************/

#ifndef TERMINAL_GAME_RUNNER_HPP
#define TERMINAL_GAME_RUNNER_HPP 1

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "GameRunnerBase.hpp"

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class TerminalGameRunner : public GameRunnerBase {

public:

  // constructors
  TerminalGameRunner () = delete;
  TerminalGameRunner (std::size_t board_dimensions, const std::shared_ptr<ScoreIface>& scorer, std::size_t max_search_depth, const std::shared_ptr<MoveFinderIface>& move_finder);

  // destructor
  ~TerminalGameRunner () override = default;

  // operators
  TerminalGameRunner (const TerminalGameRunner& in) = default;
  TerminalGameRunner& operator= (const TerminalGameRunner& rh) = default;
  TerminalGameRunner (TerminalGameRunner&& in) = default;
  TerminalGameRunner& operator= (TerminalGameRunner&& rh) = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // TERMINAL_GAME_RUNNER_HPP

