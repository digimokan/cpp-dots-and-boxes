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
#include <functional>
#include <set>
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
  void mark (std::size_t line_num);
  bool is_marked (std::size_t line_num) const;
  bool not_marked (std::size_t line_num) const;
  bool all_marked () const;
  std::size_t get_max_lines () const;
  void for_each_unmarked_line_num (const std::function<void(std::size_t line_num)>& act_on_line_num) const;

private:

  // helper methods
  std::size_t calc_num_lines (std::size_t dimensions) const;
  void init_unmarked_lines ();

  // fields
  std::vector<bool> lines;
  std::set<std::size_t> unmarked_lines;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // LINES_HPP

