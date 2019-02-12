/*******************************************************************************
module:   Player
author:   digimokan
date:     04 FEB 2019
purpose:  a player ("player one" or "computer") in a dots and boxes game
*******************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <iostream>

/*******************************************************************************
* INTERFACE
*******************************************************************************/

// types
enum class Player {
  ONE,
  COMPUTER
};

// iterating
const Player PlayerVals[] = {
  Player::ONE,
  Player::COMPUTER
};

// specialized methods
std::ostream& operator<< (std::ostream& os, const Player& player);
Player Get_opposite_player (Player player);

/*******************************************************************************
* END
*******************************************************************************/

#endif // PLAYER_HPP

