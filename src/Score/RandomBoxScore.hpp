/*******************************************************************************
module:   RandomBoxScore
author:   digimokan
date:     10 FEB 2019
purpose:  given board, return [ Human - Computer ] score
--> each completed box is worth a random point (from 1-5)
*******************************************************************************/

#ifndef RANDOM_BOX_SCORE_HPP
#define RANDOM_BOX_SCORE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <cstdint>
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "ScoreIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class Board;
enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class RandomBoxScore : public ScoreIface {

public:

  // constructors
  explicit RandomBoxScore (std::size_t dimensions);

  // destructor
  ~RandomBoxScore () override = default;

  // operators
  RandomBoxScore (const RandomBoxScore& in) = default;
  RandomBoxScore& operator= (const RandomBoxScore& rh) = default;
  RandomBoxScore (RandomBoxScore&& in) = default;
  RandomBoxScore& operator= (RandomBoxScore&& rh) = default;

  // base / derived methods
  int64_t calc_score (const Board& board) const final;
  int64_t calc_player_score (Player player, const Board& board) const final;

  // specialized methods
  int64_t get_random_box_score (std::size_t box_num) const;

private:

  // helper methods
  void init_box_scores (std::size_t dimensions);


  // fields
  std::vector<int64_t> box_scores;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // RANDOM_BOX_SCORE_HPP

