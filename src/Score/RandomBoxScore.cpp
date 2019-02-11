/*******************************************************************************
module:   RandomBoxScore
author:   digimokan
date:     10 FEB 2019
purpose:  given board, return [ Human - Computer ] score
          --> each completed box is worth a random point (from 1-5)
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include "RandomBoxScore.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

RandomBoxScore::RandomBoxScore (std::size_t dimensions) {
  this->init_box_scores(dimensions);
}

/*******************************************************************************
* BASE / DERIVED METHODS
*******************************************************************************/

int64_t RandomBoxScore::calc_score (const Board& board) const {
  int64_t oscore{ this->calc_player_score(Player::ONE, board) };
  int64_t cscore{ this->calc_player_score(Player::COMPUTER, board) };
  return (oscore - cscore);
}

int64_t RandomBoxScore::calc_player_score (Player player, const Board& board) const {
  int64_t score{ 0 };
  auto add_to_sum{ [this, &score] (auto box_num) { score += this->box_scores.at(box_num); } };
  board.for_each_player_boxmark(player, add_to_sum);
  return score;
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

int64_t RandomBoxScore::get_random_box_score (std::size_t box_num) const {
  return this->box_scores.at(box_num);
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void RandomBoxScore::init_box_scores (std::size_t dimensions) {
  const std::size_t num_boxes{ dimensions * dimensions };
  std::default_random_engine generator{ num_boxes };
  std::uniform_int_distribution<int64_t> distribution{1, 5};
  for (std::size_t box_num{0}; box_num < num_boxes; ++box_num)
    this->box_scores.emplace_back(distribution(generator));
}

