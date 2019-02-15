/*******************************************************************************
module:   MaxNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MAX node impl of SearchNodeBase
          --> has MIN node children
          --> seeks to find the MAX of its children nodes
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

MaxNode::MaxNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface)
  : SearchNodeBase{std::move(board), player_to_act, std::move(score_iface)},
    alpha{std::nullopt}
{ }

MaxNode::MaxNode (const std::shared_ptr<MinNode>& parent)
  : SearchNodeBase{parent},
    alpha{std::nullopt}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

bool MaxNode::cutoff_gen_children () const {
  if (! this->alpha.has_value())
    return false;
  if (! this->has_parent())
    return false;
  auto parent{ this->get_parent() };
  if (! parent->get_alpha_or_beta().has_value())
    return false;
  int64_t parent_beta{ parent->get_alpha_or_beta().value() };
  return (this->alpha >= parent_beta);
}

std::shared_ptr<SearchNodeIface> MaxNode::get_minimax_child () {
  return this->get_max_child();
}

void MaxNode::set_alpha_or_beta (int64_t minimax_score) {
  if (! this->alpha.has_value())
    this->alpha = minimax_score;
  else
    this->alpha = std::max(minimax_score, this->alpha.value());
}

std::optional<int64_t> MaxNode::get_alpha_or_beta () const {
  return this->alpha;
}

std::shared_ptr<SearchNodeBase> MaxNode::create_detached_child () {
  return std::make_shared<MinNode>(this->shared_from_this());
}

