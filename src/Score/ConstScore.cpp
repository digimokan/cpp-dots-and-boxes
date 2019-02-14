/*******************************************************************************
module:   ConstScore
author:   digimokan
date:     10 FEB 2019
purpose:  given board, return [ Human - Computer ] score
          --> each completed box is worth 1 point
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "ConstScore.hpp"
#include "Player.hpp"

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

int64_t ConstScore::calc_score (const Board& board) const {
  int64_t oscore{ this->calc_player_score(Player::ONE, board) };
  int64_t cscore{ this->calc_player_score(Player::COMPUTER, board) };
  return (oscore - cscore);
}

int64_t ConstScore::calc_player_score (Player player, const Board& board) const {
  int64_t score{ 0 };
  auto add_to_sum{ [&score] (auto box_num) { score++; } };
  board.for_each_player_boxmark(player, add_to_sum);
  return score;
}

