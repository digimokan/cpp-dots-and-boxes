/*******************************************************************************
module:   SearchNodeBase
author:   digimokan
date:     11 FEB 2019
purpose:  a base class impl of SearchNode
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

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
    scorer{std::move(score_iface)},
    marked_line{std::nullopt}
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

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void SearchNodeBase::mark_line (Player player, std::size_t line_num) {
  assert(! this->marked_line.has_value());
  this->marked_line = line_num;
  this->board.mark_line(player, line_num);
}

std::optional<std::size_t> SearchNodeBase::get_marked_line () const {
  return this->marked_line;
}

