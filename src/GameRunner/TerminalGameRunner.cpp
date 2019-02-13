/*******************************************************************************
module:   TerminalGameRunner
author:   digimokan
date:     13 FEB 2019
purpose:  run a dots and boxes game with terminal input/output
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "GameRunnerBase.hpp"
#include "MiniMaxMoveFinder.hpp"
#include "ScoreIface.hpp"
#include "TerminalGameRunner.hpp"
#include "TerminalMoveInput.hpp"
#include "TerminalMoveOutput.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

TerminalGameRunner::TerminalGameRunner (std::size_t board_dimensions,
        const std::shared_ptr<ScoreIface>& scorer, std::size_t max_search_depth)
  : GameRunnerBase{
      board_dimensions,
      scorer,
      max_search_depth,
      std::make_shared<MiniMaxMoveFinder>(),
      std::make_shared<TerminalMoveInput>(),
      std::make_shared<TerminalMoveOutput>()
    }
{ }

