/*******************************************************************************
module:   MiniMaxMoveFinder
author:   digimokan
date:     12 FEB 2019
purpose:  find best move using non-recursive MiniMax algorithm
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

#include "MiniMaxMoveFinder.hpp"
#include "SearchNodeIface.hpp"

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

std::shared_ptr<SearchNodeIface> MiniMaxMoveFinder::find_best_move (const std::shared_ptr<SearchNodeIface>& input_node,
      std::size_t max_search_depth) {
  std::stack<std::shared_ptr<SearchNodeIface>> nstack{{ input_node }};
  while (! nstack.empty()) {
    auto node{ nstack.top() };
    nstack.pop();
    if (node->is_terminal()) {
      node->set_minimax_score();
    } else if (node->get_depth() >= max_search_depth) {
      node->set_minimax_score();
    } else if (node->has_children()) {
      node->set_minimax_score_from_children();
    } else {
      nstack.push(node);
      auto push_child = [&nstack] (auto node) { nstack.push(node); };
      node->gen_children(push_child);
    }
  }
  return input_node->get_minimax_child();
}

