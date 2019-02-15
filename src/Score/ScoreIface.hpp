/*******************************************************************************
module:   ScoreIface
author:   digimokan
date:     10 FEB 2019
purpose:  given input board, return its [ Human - Computer ] score
*******************************************************************************/

#ifndef SCORE_IFACE_HPP
#define SCORE_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <string>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class Board;
enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class ScoreIface {

public:

  // destructor
  virtual ~ScoreIface () = default;

  // operators
  ScoreIface (const ScoreIface& in) = default;
  ScoreIface& operator= (const ScoreIface& rh) = default;
  ScoreIface (ScoreIface&& in) = default;
  ScoreIface& operator= (ScoreIface&& rh) = default;

  // base / derived methods
  virtual int64_t calc_score (const Board& board) const = 0;
  virtual int64_t calc_player_score (Player player, const Board& board) const = 0;
  virtual std::string get_box_val_string () const = 0;

protected:

  // constructors
  ScoreIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SCORE_IFACE_HPP

