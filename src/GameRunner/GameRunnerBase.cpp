/*******************************************************************************
module:   GameRunnerBase
author:   digimokan
date:     12 FEB 2019
purpose:  base impl of a GameRunner
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "GameRunnerBase.hpp"
#include "MaxNode.hpp"
#include "MoveFinderIface.hpp"
#include "MoveInputIface.hpp"
#include "MoveOutputIface.hpp"
#include "Player.hpp"
#include "ScoreIface.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

GameRunnerBase::GameRunnerBase (std::size_t board_dimensions,
      const std::shared_ptr<ScoreIface>& scorer,
      std::size_t max_search_depth,
      std::shared_ptr<MoveFinderIface> move_finder,
      std::shared_ptr<MoveInputIface> move_input,
      std::shared_ptr<MoveOutputIface> move_output)
  : max_search_depth{max_search_depth},
    first_node{std::make_shared<MaxNode>(Board{board_dimensions}, Player::ONE, scorer)},
    move_finder{std::move(move_finder)},
    move_input{std::move(move_input)},
    move_output{std::move(move_output)}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

void GameRunnerBase::run () {
  auto node{ this->first_node };
  while (! node->is_terminal()) {
    this->move_output->send(node);
    std::size_t line_num{ this->move_input->get_line_to_mark(node) };
    auto next_search_node{ node->gen_new_root(line_num) };
    node = this->move_finder->find_best_move(next_search_node, this->max_search_depth);
  }
}

