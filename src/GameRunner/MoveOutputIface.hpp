/*******************************************************************************
module:   MoveOutputIface
author:   digimokan
date:     12 FEB 2019
purpose:  given a SearchNode, output it to terminal/file/variable/etc
*******************************************************************************/

#ifndef MOVE_OUTPUT_IFACE_HPP
#define MOVE_OUTPUT_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <memory>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class SearchNodeIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MoveOutputIface {

public:

  // destructor
  virtual ~MoveOutputIface () = default;

  // operators
  MoveOutputIface (const MoveOutputIface& in) = default;
  MoveOutputIface& operator= (const MoveOutputIface& rh) = default;
  MoveOutputIface (MoveOutputIface&& in) = default;
  MoveOutputIface& operator= (MoveOutputIface&& rh) = default;

  // base / derived methods
  virtual void send (std::shared_ptr<SearchNodeIface> node) = 0;

protected:

  // constructors
  MoveOutputIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MOVE_OUTPUT_IFACE_HPP

