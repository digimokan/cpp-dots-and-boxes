/*******************************************************************************
module:   GameRunnerBase
author:   digimokan
date:     12 FEB 2019
purpose:  base impl of a GameRunner
*******************************************************************************/

#ifndef GAME_RUNNER_BASE_HPP
#define GAME_RUNNER_BASE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "GameRunnerIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class MoveFinderIface;
class MoveInputIface;
class MoveOutputIface;
class ScoreIface;
class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class GameRunnerBase : public GameRunnerIface {

public:

  // constructors
  GameRunnerBase () = delete;

  // destructor
  ~GameRunnerBase () override = default;

  // operators
  GameRunnerBase (const GameRunnerBase& in) = default;
  GameRunnerBase& operator= (const GameRunnerBase& rh) = default;
  GameRunnerBase (GameRunnerBase&& in) = default;
  GameRunnerBase& operator= (GameRunnerBase&& rh) = default;

  // base / derived methods
  void run () final;

protected:

  // constructors
  GameRunnerBase (std::size_t board_dimensions, const std::shared_ptr<ScoreIface>& scorer, std::size_t max_search_depth, std::shared_ptr<MoveFinderIface> move_finder, std::shared_ptr<MoveInputIface> move_input, std::shared_ptr<MoveOutputIface> move_output);

private:

  // fields
  std::size_t max_search_depth;
  std::shared_ptr<SearchNodeIface> first_node;
  std::shared_ptr<MoveFinderIface> move_finder;
  std::shared_ptr<MoveInputIface> move_input;
  std::shared_ptr<MoveOutputIface> move_output;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // GAME_RUNNER_BASE_HPP

