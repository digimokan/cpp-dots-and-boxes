/*******************************************************************************
module:   main
author:   digimokan
date:     02 FEB 2018 (created)
purpose:  run Dots and Boxes program
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <memory>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "ConstScore.hpp"
#include "TerminalGameRunner.hpp"

/*******************************************************************************
* MAIN
*******************************************************************************/

int main (int argc, char* argv[]) {
  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t max_search_depth{ 5 };
  auto scorer{ std::make_shared<ConstScore>() };
  TerminalGameRunner game_runner{ dimensions, scorer, max_search_depth };
  game_runner.run();
  return (0);
}

