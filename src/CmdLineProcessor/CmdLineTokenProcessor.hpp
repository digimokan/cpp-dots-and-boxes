/*******************************************************************************
module:   CmdLineTokenProcessor
author:   digimokan
date:     12 JAN 2019
purpose:  process program-input command-line tokens
*******************************************************************************/

#ifndef CMD_LINE_TOKEN_PROCESSOR_HPP
#define CMD_LINE_TOKEN_PROCESSOR_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <functional>
#include <getopt.h>
#include <memory>
#include <string>
#include <vector>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class MoveFinderIface;
class ScoreIface;
class TerminalGameRunner;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class CmdLineTokenProcessor {

public:

  // constructors
  CmdLineTokenProcessor () = delete;
  CmdLineTokenProcessor (int argc, char* argv[]);

  // destructor
  ~CmdLineTokenProcessor () = default;

  // operators
  CmdLineTokenProcessor (const CmdLineTokenProcessor& in) = delete;
  CmdLineTokenProcessor& operator= (const CmdLineTokenProcessor& rh) = delete;
  CmdLineTokenProcessor (CmdLineTokenProcessor&& in) = delete;
  CmdLineTokenProcessor& operator= (CmdLineTokenProcessor&& rh) = delete;

  // specialized methods
  std::shared_ptr<TerminalGameRunner> create_game_runner ();

private:

  // cmd-line input fields
  const char* program_name;
  std::vector<char*> tokens;
  const char* short_opts;
  const std::vector<option> long_opts_map;

  // processing/return fields
  std::size_t board_dimensions;
  std::shared_ptr<ScoreIface> scorer;
  std::size_t max_search_depth;
  std::shared_ptr<MoveFinderIface> move_finder;
  std::function<std::shared_ptr<ScoreIface>(std::size_t dimensions)> score_maker;

  // helper methods
  void process_options ();
  void process_non_option_args ();
  void process_opt (int opt);
  void print_err_msg (const std::string& err_msg);

  // option handlers
  void handle_help (int exit_code);
  void handle_board_dimensions (std::size_t in_dimensions);
  void handle_const_box_score ();
  void handle_random_box_score ();
  void handle_max_search_depth (std::size_t in_depth);
  void handle_minimax_search ();
  void handle_alpha_beta_minimax_search ();

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // CMD_LINE_TOKEN_PROCESSOR_HPP

