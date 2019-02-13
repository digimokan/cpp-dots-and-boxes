/*******************************************************************************
module:   MoveInputIface
author:   digimokan
date:     12 FEB 2019
purpose:  get input for a move (i.e., the line-number) from terminal/file/etc
*******************************************************************************/

#ifndef MOVE_INPUT_IFACE_HPP
#define MOVE_INPUT_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <memory>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MoveInputIface {

public:

  // destructor
  virtual ~MoveInputIface () = default;

  // operators
  MoveInputIface (const MoveInputIface& in) = default;
  MoveInputIface& operator= (const MoveInputIface& rh) = default;
  MoveInputIface (MoveInputIface&& in) = default;
  MoveInputIface& operator= (MoveInputIface&& rh) = default;

  // base / derived methods
  virtual std::size_t get_line_to_mark (std::shared_ptr<SearchNodeIface> node) = 0;

protected:

  // constructors
  MoveInputIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MOVE_INPUT_IFACE_HPP

