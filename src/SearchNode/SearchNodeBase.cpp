/*******************************************************************************
module:   SearchNodeBase
author:   digimokan
date:     11 FEB 2019
purpose:  a base class impl of SearchNode
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <algorithm>
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
    marked_line{std::nullopt},
    scorer{std::move(score_iface)},
    minimax_score{std::nullopt},
    depth{0}
{ }

SearchNodeBase::SearchNodeBase (const std::shared_ptr<SearchNodeBase>& parent)
  : board{parent->board},
    player_to_act{Get_opposite_player(parent->get_player_to_act())},
    marked_line{std::nullopt},
    scorer{parent->scorer},
    minimax_score{std::nullopt},
    depth{parent->get_depth() + 1},
    parent{parent}
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

void SearchNodeBase::set_minimax_score () {
  this->minimax_score = this->calc_score();
}

int64_t SearchNodeBase::get_minimax_score () {
  assert(this->minimax_score.has_value());
  return this->minimax_score.value();
}

bool SearchNodeBase::has_parent () const {
  return (this->depth > 0);
}

std::shared_ptr<SearchNodeIface> SearchNodeBase::get_parent () const {
  assert(! this->parent.expired());
  return this->parent.lock();
}

bool SearchNodeBase::has_children () const {
  return (! this->children.empty());
}

std::size_t SearchNodeBase::get_depth () const {
  return this->depth;
}

void SearchNodeBase::set_depth (std::size_t in_depth) {
  this->depth = in_depth;
}

Player SearchNodeBase::get_player_to_act () const {
  return this->player_to_act;
}

Board SearchNodeBase::get_board () const {
  return this->board;
}

std::shared_ptr<ScoreIface> SearchNodeBase::get_scorer () const {
  return this->scorer;
}

std::optional<std::size_t> SearchNodeBase::get_marked_line () const {
  return this->marked_line;
}

void SearchNodeBase::add_child (const std::shared_ptr<SearchNodeIface>& child) {
  this->children.push_back(child);
}

void SearchNodeBase::gen_children (std::function<void(std::shared_ptr<SearchNodeIface>)> act_on_child) {
  for (const auto line_num : this->board.get_unmarked_lines()) {
    auto child{ this->create_detached_child() };
    child->mark_line(this->get_player_to_act(), line_num);
    this->add_child(child);
    act_on_child(child);
    if (this->cutoff_gen_children())
      break;
  }
}

std::shared_ptr<SearchNodeIface> SearchNodeBase::gen_new_root (std::size_t line_num) {
  auto child{ this->create_detached_child() };
  child->set_depth(0);
  child->mark_line(this->get_player_to_act(), line_num);
  return child;
}

void SearchNodeBase::set_minimax_score_from_children () {
  assert(this->has_children());
  this->minimax_score = this->get_minimax_child()->get_minimax_score();
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

void SearchNodeBase::mark_line (Player player, std::size_t line_num) {
  assert(! this->marked_line.has_value());
  this->marked_line = line_num;
  this->board.mark_line(player, line_num);
}

std::shared_ptr<SearchNodeIface> SearchNodeBase::get_max_child () const {
  auto comp = [] (const auto& left, const auto& right) {
    int64_t left_score{ left->get_minimax_score() };
    int64_t right_score{ right->get_minimax_score() };
    return (left_score < right_score);
  };
  auto it{ std::max_element(this->children.cbegin(), this->children.cend(), comp) };
  assert(it != this->children.cend());
  return *it;
}

std::shared_ptr<SearchNodeIface> SearchNodeBase::get_min_child () const {
  auto comp = [] (const auto& left, const auto& right) {
    int64_t left_score{ left->get_minimax_score() };
    int64_t right_score{ right->get_minimax_score() };
    return (left_score < right_score);
  };
  auto it{ std::min_element(this->children.cbegin(), this->children.cend(), comp) };
  assert(it != this->children.cend());
  return *it;
}

