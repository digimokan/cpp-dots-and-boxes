/*******************************************************************************
module:   CmdLineTokenProcessor
author:   digimokan
date:     12 JAN 2019
purpose:  process program-input command-line tokens
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdlib>
#include <functional>
#include <getopt.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "CmdLineTokenProcessor.hpp"
#include "ConstScore.hpp"
#include "MiniMaxMoveFinder.hpp"
#include "RandomBoxScore.hpp"
#include "TerminalGameRunner.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

CmdLineTokenProcessor::CmdLineTokenProcessor (int argc, char* argv[])
  : program_name{*argv},
    tokens{argv, argv + argc},
    short_opts{"hb:crs:ma"},
    long_opts_map{
      {"help",                      no_argument,       nullptr, 'h'},
      {"board-dimensions",          required_argument, nullptr, 'b'},
      {"const-box-score",           no_argument,       nullptr, 'c'},
      {"random-box-score",          no_argument,       nullptr, 'r'},
      {"max-search-depth",          required_argument, nullptr, 's'},
      {"minimax-search",            no_argument,       nullptr, 'm'},
      {"alpha-beta-minimax-search", no_argument,       nullptr, 'a'},
      {nullptr,                     no_argument,       nullptr,  0}
    },
    board_dimensions{3},
    scorer{std::make_shared<ConstScore>()},
    max_search_depth{2},
    move_finder{std::make_shared<MiniMaxMoveFinder>()},
    score_maker{[] (std::size_t dimensions) { return std::make_shared<ConstScore>(); }}
{ }

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::shared_ptr<TerminalGameRunner> CmdLineTokenProcessor::create_game_runner () {
  this->process_options();
  this->process_non_option_args();
  return std::make_shared<TerminalGameRunner>(
    this->board_dimensions,
    this->scorer,
    this->max_search_depth,
    this->move_finder
  );
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void CmdLineTokenProcessor::process_options () {
  while (true) {
    const int opt = getopt_long(tokens.size(), tokens.data(), this->short_opts, this->long_opts_map.data(), nullptr);
    if (opt == -1)
      break;
    this->process_opt(opt);
  }
}

void CmdLineTokenProcessor::process_non_option_args () {
  if ((tokens.size() - optind) > 0)
    this->print_err_msg("found trailing non-option arg - none are allowed.");
}

void CmdLineTokenProcessor::process_opt (int opt) {
  switch (opt) {
  case 'h':
    this->handle_help(EXIT_SUCCESS);
    break;
  case 'b':
    this->handle_board_dimensions(static_cast<std::size_t>(std::stoul(optarg)));
    break;
  case 'c':
    this->handle_const_box_score();
    break;
  case 'r':
    this->handle_random_box_score();
    break;
  case 's':
    this->handle_max_search_depth(static_cast<std::size_t>(std::stoul(optarg)));
    break;
  case 'm':
    this->handle_minimax_search();
    break;
  case 'a':
    this->handle_alpha_beta_minimax_search();
    break;
  default:
    this->print_err_msg("uknown error processing cmd line");
    break;
  }
}

void CmdLineTokenProcessor::print_err_msg (const std::string& err_msg) {
  std::cerr << "ERROR: " << err_msg << '\n' << '\n';
  this->handle_help(EXIT_FAILURE);
}

/*******************************************************************************
* OPTION HANDLERS
*******************************************************************************/

void CmdLineTokenProcessor::handle_help (int exit_code) {
  std::cout << "USAGE" << '\n';
  std::cout << "  " << this->program_name << "  "
            << "-h" << '\n';
  std::cout << "  " << this->program_name << "  "
            << "[-b <n>]  [-c|-r]  [-s <n>]  [-m|-a]" << '\n';
  std::cout << "OPTIONS" << '\n';
  std::cout << "  " << "-h, --help" << '\n' << "      "
            << "print this help message" << '\n';
  std::cout << "  " << "-b <n>, --board-dimensions=<n>" << '\n' << "      "
            << "play on an n x n board (default 3 x 3)" << '\n';
  std::cout << "  " << "-c, --const-box-score" << '\n' << "      "
            << "use constant box scoring (each box is worth 1 point)" << '\n';
  std::cout << "  " << "-r, --random-box-score" << '\n' << "      "
            << "use random box scoring (each box is worth random 1-5 points)" << '\n';
  std::cout << "  " << "-s <n>, --max-search-depth=<n>" << '\n' << "      "
            << "have AI search n-moves-deep (default 2-moves-deep)" << '\n';
  std::cout << "  " << "-m, --minimax-search" << '\n' << "      "
            << "have AI search with minimax algorithm" << '\n';
  std::cout << "  " << "-a, --alpha-beta-minimax-search" << '\n' << "      "
            << "have AI search with alpha-beta minimax algorithm" << '\n';
  exit(exit_code);
}

void CmdLineTokenProcessor::handle_board_dimensions (std::size_t in_dimensions) {
  this->board_dimensions = in_dimensions;
  this->scorer = this->score_maker(this->board_dimensions);
}

void CmdLineTokenProcessor::handle_const_box_score () {
  this->score_maker = [] (std::size_t dimensions) { return std::make_shared<ConstScore>(); };
  this->scorer = this->score_maker(this->board_dimensions);
}

void CmdLineTokenProcessor::handle_random_box_score () {
  this->score_maker = [] (std::size_t dimensions) { return std::make_shared<RandomBoxScore>(dimensions); };
  this->scorer = this->score_maker(this->board_dimensions);
}

void CmdLineTokenProcessor::handle_max_search_depth (std::size_t in_depth) {
  this->max_search_depth = in_depth;
}

void CmdLineTokenProcessor::handle_minimax_search () {
  this->move_finder = std::make_shared<MiniMaxMoveFinder>();
}

void CmdLineTokenProcessor::handle_alpha_beta_minimax_search () {
  this->move_finder = std::make_shared<MiniMaxMoveFinder>();
}

