/*******************************************************************************
module:   AlphaBetaMoveFinder
author:   digimokan
date:     12 FEB 2019
purpose:  find best move using non-recursive alpha-beta minimax algorithm
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>
#include <stack>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "AlphaBetaMoveFinder.hpp"
#include "Board.hpp"
#include "SearchNodeIface.hpp"

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

std::shared_ptr<SearchNodeIface> AlphaBetaMoveFinder::find_best_move (const std::shared_ptr<SearchNodeIface>& input_node,
      std::size_t max_search_depth) {
  while (! this->nstack.empty())
    this->nstack.pop();
  this->nstack.push(input_node);
  while (! this->nstack.empty()) {
    auto node{ this->nstack.top() };
    this->nstack.pop();
    if (node->is_terminal())
      this->update_node_parent_score_alpha_beta(node);
    else if (node->get_depth() >= max_search_depth)
      this->update_node_parent_score_alpha_beta(node);
    else if (node->has_children())
      this->update_node_parent_score_alpha_beta_from_children(node);
    else
      this->gen_children_with_cutoff(node, max_search_depth);
  }
  return input_node->get_minimax_child();
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void AlphaBetaMoveFinder::update_node_parent_score_alpha_beta (const std::shared_ptr<SearchNodeIface>& node) {
  node->set_minimax_score();
  node->set_alpha_or_beta(node->get_minimax_score());
  this->update_parent_alpha_beta(node);
}

void AlphaBetaMoveFinder::update_node_parent_score_alpha_beta_from_children (const std::shared_ptr<SearchNodeIface>& node) {
  node->set_minimax_score_from_children();
  node->set_alpha_or_beta(node->get_minimax_score());
  this->update_parent_alpha_beta(node);
}

void AlphaBetaMoveFinder::update_parent_alpha_beta (const std::shared_ptr<SearchNodeIface>& node) {
  if (! node->has_parent())
    return;
  auto parent{ node->get_parent() };
  parent->set_alpha_or_beta(node->get_minimax_score());
}

void AlphaBetaMoveFinder::gen_children_with_cutoff (const std::shared_ptr<SearchNodeIface>& node,
      std::size_t max_search_depth) {
  this->nstack.push(node);
  auto process_child = [this, max_search_depth] (auto child) {
    if (child->is_terminal())
      this->update_node_parent_score_alpha_beta(child);
    else if (child->get_depth() >= max_search_depth)
      this->update_node_parent_score_alpha_beta(child);
    else
      this->nstack.push(child);
  };
  node->gen_children(process_child);
}

