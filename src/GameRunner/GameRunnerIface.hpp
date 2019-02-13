/*******************************************************************************
module:   GameRunnerIface
author:   digimokan
date:     12 FEB 2019
purpose:  given means of input and output, run a dots and boxes game
*******************************************************************************/

#ifndef GAME_RUNNER_IFACE_HPP
#define GAME_RUNNER_IFACE_HPP 1

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class GameRunnerIface {

public:

  // destructor
  virtual ~GameRunnerIface () = default;

  // operators
  GameRunnerIface (const GameRunnerIface& in) = default;
  GameRunnerIface& operator= (const GameRunnerIface& rh) = default;
  GameRunnerIface (GameRunnerIface&& in) = default;
  GameRunnerIface& operator= (GameRunnerIface&& rh) = default;

  // base / derived methods
  virtual void run () = 0;

protected:

  // constructors
  GameRunnerIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // GAME_RUNNER_IFACE_HPP

