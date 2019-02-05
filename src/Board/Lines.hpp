/*******************************************************************************
module:   Lines
author:   digimokan
date:     04 FEB 2019
purpose:  data structure containing the unique lines of a dots and boxes board
*******************************************************************************/

#ifndef LINES_HPP
#define LINES_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <vector>

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class Lines {

public:

  // constructors
  Lines () = delete;
  explicit Lines (std::size_t dimensions);

  // destructor
  ~Lines () = default;

  // operators
  Lines (const Lines& in) = default;
  Lines& operator= (const Lines& rh) = default;
  Lines (Lines&& in) = default;
  Lines& operator= (Lines&& rh) = default;

  // specialized methods
  std::size_t get_num_lines () const;

private:

  // helper methods
  std::size_t calc_num_lines (std::size_t dimensions) const;

  // fields
  std::vector<bool> lines;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // LINES_HPP

