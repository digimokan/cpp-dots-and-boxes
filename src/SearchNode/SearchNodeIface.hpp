/*******************************************************************************
module:   SearchNodeIface
author:   digimokan
date:     11 FEB 2019
purpose:  a dots and boxes search node
*******************************************************************************/

#ifndef SEARCH_NODE_IFACE_HPP
#define SEARCH_NODE_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class Board;
enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class SearchNodeIface {

public:

  // destructor
  virtual ~SearchNodeIface () = default;

  // operators
  SearchNodeIface (const SearchNodeIface& in) = default;
  SearchNodeIface& operator= (const SearchNodeIface& rh) = default;
  SearchNodeIface (SearchNodeIface&& in) = default;
  SearchNodeIface& operator= (SearchNodeIface&& rh) = default;

  // base / derived methods
  virtual bool is_terminal () const = 0;
  virtual int64_t calc_score () const = 0;
  virtual int64_t calc_player_score (Player player) const = 0;
  virtual bool has_parent () const = 0;
  virtual bool not_has_parent () const = 0;
  virtual bool has_children () const = 0;
  virtual bool not_has_children () const = 0;
  virtual std::size_t get_depth () const = 0;

protected:

  // constructors
  SearchNodeIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SEARCH_NODE_IFACE_HPP
