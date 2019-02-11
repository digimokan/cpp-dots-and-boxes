/*******************************************************************************
module:   ConstScore
author:   digimokan
date:     10 FEB 2019
purpose:  given board, return [ Human - Computer ] score
          --> each completed box is worth 1 point
*******************************************************************************/

#ifndef CONST_SCORE_HPP
#define CONST_SCORE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>

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

class ConstScore : public ScoreIface {

public:

  // constructors
  ConstScore () = default;

  // destructor
  ~ConstScore () override = default;

  // operators
  ConstScore (const ConstScore& in) = default;
  ConstScore& operator= (const ConstScore& rh) = default;
  ConstScore (ConstScore&& in) = default;
  ConstScore& operator= (ConstScore&& rh) = default;

  // base / derived methods
  int64_t calc_score (const Board& board) final;

private:

  // helper methods
  int64_t calc_player_score (Player player, const Board& board) const;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // CONST_SCORE_HPP

