/*******************************************************************************
module:   MoveFinderIface
author:   digimokan
date:     12 FEB 2019
purpose:  given input SearchNode and max depth, find best move
*******************************************************************************/

#ifndef MOVE_FINDER_IFACE_HPP
#define MOVE_FINDER_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <memory>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MoveFinderIface {

public:

  // destructor
  virtual ~MoveFinderIface () = default;

  // operators
  MoveFinderIface (const MoveFinderIface& in) = default;
  MoveFinderIface& operator= (const MoveFinderIface& rh) = default;
  MoveFinderIface (MoveFinderIface&& in) = default;
  MoveFinderIface& operator= (MoveFinderIface&& rh) = default;

  // base / derived methods
  virtual std::shared_ptr<SearchNodeIface> find_best_move (const std::shared_ptr<SearchNodeIface>& input_node, std::size_t max_search_depth) = 0;

protected:

  // constructors
  MoveFinderIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MOVE_FINDER_IFACE_HPP

