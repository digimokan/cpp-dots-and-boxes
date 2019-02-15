/*******************************************************************************
module:   MinNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MIN node impl of SearchNodeBase
          --> has MAX node children
          --> seeks to find the MIN of its children nodes
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <algorithm>
#include <cstdint>
#include <optional>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MaxNode.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

MinNode::MinNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface)
  : SearchNodeBase{std::move(board), player_to_act, std::move(score_iface)},
    beta{std::nullopt}
{ }

MinNode::MinNode (const std::shared_ptr<MaxNode>& parent)
  : SearchNodeBase{parent},
    beta{std::nullopt}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

bool MinNode::cutoff_gen_children () const {
  if (! this->beta.has_value())
    return false;
  if (! this->has_parent())
    return false;
  auto parent{ this->get_parent() };
  if (! parent->get_alpha_or_beta().has_value())
    return false;
  int64_t parent_alpha{ parent->get_alpha_or_beta().value() };
  return (this->beta <= parent_alpha);
}

std::shared_ptr<SearchNodeIface> MinNode::get_minimax_child () {
  return this->get_min_child();
}

void MinNode::set_alpha_or_beta (int64_t minimax_score) {
  if (! this->beta.has_value())
    this->beta = minimax_score;
  else
    this->beta = std::min(minimax_score, this->beta.value());
}

std::optional<int64_t> MinNode::get_alpha_or_beta () const {
  return this->beta;
}

std::shared_ptr<SearchNodeBase> MinNode::create_detached_child () {
  return std::make_shared<MaxNode>(this->shared_from_this());
}

