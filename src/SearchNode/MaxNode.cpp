/*******************************************************************************
module:   MaxNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MAX node impl of SearchNodeBase
          --> has MIN node children
          --> seeks to find the MAX of its children nodes
*******************************************************************************/

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MaxNode.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

MaxNode::MaxNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface)
  : SearchNodeBase{std::move(board), player_to_act, std::move(score_iface)}
{ }

MaxNode::MaxNode (const std::shared_ptr<MinNode>& parent)
  : SearchNodeBase{parent}
{ }

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

std::shared_ptr<SearchNodeIface> MaxNode::get_minimax_child () {
  return this->get_max_child();
}

std::shared_ptr<SearchNodeBase> MaxNode::create_detached_child () {
  return std::make_shared<MinNode>(this->shared_from_this());
}

