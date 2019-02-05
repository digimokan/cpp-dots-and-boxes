/*******************************************************************************
module:   BoxMarks
author:   digimokan
date:     04 FEB 2019
purpose:  map of box_num -> marking_player
*******************************************************************************/

#ifndef BOX_MARKS_HPP
#define BOX_MARKS_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <unordered_map>
#include <unordered_set>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class BoxMarks {

public:

  // constructors
  BoxMarks () = delete;
  explicit BoxMarks (std::size_t board_dimensions);

  // destructor
  ~BoxMarks () = default;

  // operators
  BoxMarks (const BoxMarks& in) = default;
  BoxMarks& operator= (const BoxMarks& rh) = default;
  BoxMarks (BoxMarks&& in) = default;
  BoxMarks& operator= (BoxMarks&& rh) = default;

  // specialized methods
  std::size_t get_num_boxes () const;
  std::size_t get_board_dimensions () const;
  bool is_marked (std::size_t box_num) const;
  bool not_marked (std::size_t box_num) const;
  void mark (std::size_t box_num, Player player);
  std::size_t get_num_unmarked () const;
  std::size_t get_num_marked () const;
  bool all_marked () const;

private:

  // fields
  std::unordered_map<std::size_t, Player> marks;
  std::unordered_set<std::size_t> unmarked_boxnums;
  std::unordered_set<std::size_t> marked_boxnums;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // BOX_MARKS_HPP

