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
    parent{std::nullopt},
    marked_line{std::nullopt}
{ }

SearchNodeBase::SearchNodeBase (std::shared_ptr<SearchNodeBase> parent)
  : board{parent->board},
    scorer{parent->scorer},
    parent{parent},
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

bool SearchNodeBase::has_parent () const {
  return this->parent.has_value();
}

bool SearchNodeBase::not_has_parent () const {
  return (! this->has_parent());
}

bool SearchNodeBase::has_children () const {
  return (! this->children.empty());
}

bool SearchNodeBase::not_has_children () const {
  return (! this->has_children());
}

std::optional<std::shared_ptr<SearchNodeBase>> SearchNodeBase::get_parent () const {
  return this->parent;
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

void SearchNodeBase::add_child (const std::shared_ptr<SearchNodeBase>& child) {
  this->children.push_back(child);
}

