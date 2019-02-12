/*******************************************************************************
module:   Player
author:   digimokan
date:     04 FEB 2019
purpose:  a player ("player one" or "computer") in a dots and boxes game
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cassert>
#include <iostream>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Player.hpp"

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::ostream& operator<< (std::ostream& os, const Player& player) {
  switch (player) {
    case Player::ONE:
      os << u8"1";
      break;
    case Player::COMPUTER:
      os << u8"C";
      break;
    default:
      os << u8"?";
      break;
  }
  return os;
}

Player Get_opposite_player (Player player) {
  Player opposite;
  switch (player) {
    case Player::ONE:
      opposite = Player::COMPUTER;
      break;
    case Player::COMPUTER:
      opposite = Player::ONE;
      break;
    default:
      assert(false);
      break;
  }
  return opposite;
}

