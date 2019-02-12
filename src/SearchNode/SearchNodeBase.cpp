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

SearchNodeBase::SearchNodeBase (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface)
  : board{std::move(board)},
    player_to_act{player_to_act},
    scorer{std::move(score_iface)},
    parent{std::nullopt},
    marked_line{std::nullopt},
    depth{0}
{ }

SearchNodeBase::SearchNodeBase (std::shared_ptr<SearchNodeBase> parent)
  : board{parent->board},
    player_to_act{Get_opposite_player(parent->get_player_to_act())},
    scorer{parent->scorer},
    parent{parent},
    marked_line{std::nullopt},
    depth{parent->get_depth() + 1}
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

std::size_t SearchNodeBase::get_depth () const {
  return this->depth;
}

Player SearchNodeBase::get_player_to_act () const {
  return this->player_to_act;
}

void SearchNodeBase::gen_children (std::function<void(std::shared_ptr<SearchNodeIface>)> act_on_child) {
  for (const auto line_num : this->board.get_unmarked_lines()) {
    auto child{ this->create_detached_child() };
    child->mark_line(this->get_player_to_act(), line_num);
    this->add_child(child);
    act_on_child(child);
  }
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::optional<std::shared_ptr<SearchNodeBase>> SearchNodeBase::get_parent () const {
  return this->parent;
}

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

