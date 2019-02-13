/*******************************************************************************
module:   MiniMaxMoveFinder
author:   digimokan
date:     12 FEB 2019
purpose:  find best move using non-recursive MiniMax algorithm
*******************************************************************************/

#ifndef MINI_MAX_MOVE_FINDER_HPP
#define MINI_MAX_MOVE_FINDER_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "MoveFinderIface.hpp"

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MiniMaxMoveFinder : public MoveFinderIface {

public:

  // constructors
  MiniMaxMoveFinder () = default;

  // destructor
  ~MiniMaxMoveFinder () override = default;

  // operators
  MiniMaxMoveFinder (const MiniMaxMoveFinder& in) = default;
  MiniMaxMoveFinder& operator= (const MiniMaxMoveFinder& rh) = default;
  MiniMaxMoveFinder (MiniMaxMoveFinder&& in) = default;
  MiniMaxMoveFinder& operator= (MiniMaxMoveFinder&& rh) = default;

  // base / derived methods
  std::shared_ptr<SearchNodeIface> find_best_move (const std::shared_ptr<SearchNodeIface>& input_node, std::size_t max_search_depth) final;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MINI_MAX_MOVE_FINDER_HPP

