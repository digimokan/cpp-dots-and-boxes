/*******************************************************************************
module:   AlphaBetaMoveFinder
author:   digimokan
date:     14 FEB 2019
purpose:  find best move using non-recursive alpha-beta minimax algorithm
*******************************************************************************/

#ifndef ALPHA_BETA_MOVE_FINDER_HPP
#define ALPHA_BETA_MOVE_FINDER_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <stack>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MoveFinderIface.hpp"

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class AlphaBetaMoveFinder : public MoveFinderIface {

public:

  // constructors
  AlphaBetaMoveFinder () = default;

  // destructor
  ~AlphaBetaMoveFinder () override = default;

  // operators
  AlphaBetaMoveFinder (const AlphaBetaMoveFinder& in) = default;
  AlphaBetaMoveFinder& operator= (const AlphaBetaMoveFinder& rh) = default;
  AlphaBetaMoveFinder (AlphaBetaMoveFinder&& in) = default;
  AlphaBetaMoveFinder& operator= (AlphaBetaMoveFinder&& rh) = default;

  // base / derived methods
  std::shared_ptr<SearchNodeIface> find_best_move (const std::shared_ptr<SearchNodeIface>& input_node, std::size_t max_search_depth) final;

private:

  // helper methods
  void update_node_parent_score_alpha_beta (const std::shared_ptr<SearchNodeIface>& node);
  void update_node_parent_score_alpha_beta_from_children (const std::shared_ptr<SearchNodeIface>& node);
  void update_parent_alpha_beta (const std::shared_ptr<SearchNodeIface>& node);
  void gen_children_with_cutoff (const std::shared_ptr<SearchNodeIface>& node, std::size_t max_search_depth);

  // fields
  std::stack<std::shared_ptr<SearchNodeIface>> nstack;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // ALPHA_BETA_MOVE_FINDER_HPP

