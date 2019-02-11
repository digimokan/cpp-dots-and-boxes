/*******************************************************************************
module:   SearchNodeBase
author:   digimokan
date:     11 FEB 2019
purpose:  a base class impl of SearchNode
*******************************************************************************/

#ifndef SEARCH_NODE_BASE_HPP
#define SEARCH_NODE_BASE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "SearchNodeIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class ScoreIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class SearchNodeBase : public SearchNodeIface {

public:

  // constructors
  SearchNodeBase () = delete;

  // destructor
  ~SearchNodeBase () override = default;

  // operators
  SearchNodeBase (const SearchNodeBase& in) = default;
  SearchNodeBase& operator= (const SearchNodeBase& rh) = default;
  SearchNodeBase (SearchNodeBase&& in) = default;
  SearchNodeBase& operator= (SearchNodeBase&& rh) = default;

  // base / derived methods
  bool is_terminal () const final;
  int64_t calc_score () const final;

protected:

  // constructors
  SearchNodeBase (Board board, std::shared_ptr<ScoreIface> score_iface);

  // fields
  Board board;
  std::shared_ptr<ScoreIface> scorer;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SEARCH_NODE_BASE_HPP

