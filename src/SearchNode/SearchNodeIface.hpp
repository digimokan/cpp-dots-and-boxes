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

protected:

  // constructors
  SearchNodeIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SEARCH_NODE_IFACE_HPP

