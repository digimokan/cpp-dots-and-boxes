/*******************************************************************************
module:   TerminalMoveOutput
author:   digimokan
date:     13 FEB 2019
purpose:  output a SearchNode's current board, scores, etc to the terminal
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include "SearchNodeIface.hpp"
#include "TerminalMoveOutput.hpp"

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

void TerminalMoveOutput::send (std::shared_ptr<SearchNodeIface> node) {
  std::cout << '\n';
  std::cout << node->get_board() << '\n';
  std::cout << '\n';
  std::cout << "Last Line Marked: " << std::right << std::setw(3) << this->last_line_marked(node) << "     ";
  std::cout << "Player 1 Score: " << node->calc_player_score(Player::ONE) << '\n';
  std::cout << "Player To Act:      " << node->get_player_to_act() << "     ";
  std::cout << "Player C Score: " << node->calc_player_score(Player::COMPUTER) << '\n';
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

std::string TerminalMoveOutput::last_line_marked (const std::shared_ptr<SearchNodeIface>& node) const {
  auto last_line{ node->get_marked_line() };
  if (last_line.has_value())
    return std::to_string(last_line.value());
  return "N/A";
}

