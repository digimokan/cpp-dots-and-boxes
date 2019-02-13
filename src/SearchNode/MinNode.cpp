/*******************************************************************************
module:   MinNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MIN node impl of SearchNodeBase
          --> has MAX node children
          --> seeks to find the MIN of its children nodes
*******************************************************************************/

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MaxNode.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

MinNode::MinNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface)
  : SearchNodeBase{std::move(board), player_to_act, std::move(score_iface)}
{ }

MinNode::MinNode (const std::shared_ptr<MaxNode>& parent)
  : SearchNodeBase{parent}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

std::shared_ptr<SearchNodeIface> MinNode::get_minimax_child () {
  return this->get_min_child();
}

std::shared_ptr<SearchNodeBase> MinNode::create_detached_child () {
  return std::make_shared<MaxNode>(this->shared_from_this());
}

