/*******************************************************************************
module:   main
author:   digimokan
date:     02 FEB 2018 (created)
purpose:  run Dots and Boxes program
*******************************************************************************/

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "CmdLineTokenProcessor.hpp"
#include "TerminalGameRunner.hpp"

/*******************************************************************************
* MAIN
*******************************************************************************/

int main (int argc, char* argv[]) {
  CmdLineTokenProcessor token_proc{ argc, argv };
  auto game_runner{ token_proc.create_game_runner() };
  game_runner->run();
  return (0);
}

