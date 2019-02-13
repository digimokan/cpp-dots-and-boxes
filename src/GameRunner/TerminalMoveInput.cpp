/*******************************************************************************
module:   TerminalMoveInput
author:   digimokan
date:     13 FEB 2019
purpose:  for current board, collect move input (line num to mark) from terminal
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <iostream>
#include <optional>
#include <string>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "SearchNodeIface.hpp"
#include "TerminalMoveInput.hpp"

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

std::size_t TerminalMoveInput::get_line_to_mark (const std::shared_ptr<SearchNodeIface>& node) {
  Board current_board{ node->get_board() };
  std::optional<std::size_t> line_to_mark{ std::nullopt };
  while (line_to_mark == std::nullopt) {
    std::cout << "\nEnter [row][column] to mark: ";
    std::string row_col_code{};
    std::cin >> row_col_code;
    if (! current_board.is_row_col_code_valid(row_col_code)) {
      std::cout << "\nInvalid [row][column] code, try again.\n";
    } else if (current_board.is_line_marked(current_board.get_line_num(row_col_code))) {
      std::cout << "\nLine already marked, try again.\n";
    } else {
      line_to_mark = current_board.get_line_num(row_col_code);
    }
  }
  return line_to_mark.value();
}

