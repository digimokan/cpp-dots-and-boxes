/*******************************************************************************
module:   SearchNodeBase
author:   digimokan
date:     11 FEB 2019
purpose:  a base class impl of SearchNode
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include "ScoreIface.hpp"
#include "SearchNodeBase.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

SearchNodeBase::SearchNodeBase (Board board, std::shared_ptr<ScoreIface> score_iface)
  : board{std::move(board)},
    scorer{std::move(score_iface)}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

bool SearchNodeBase::is_terminal () const {
  return this->board.is_completed();
}

int64_t SearchNodeBase::calc_score () const {
  return this->scorer->calc_score(this->board);
}

int64_t SearchNodeBase::calc_player_score (Player player) const {
  return this->scorer->calc_player_score(player, this->board);
}

