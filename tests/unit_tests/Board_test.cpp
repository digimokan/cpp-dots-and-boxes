/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <sstream>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("no lines marked") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  Board board{ dimensions };

  SUBCASE("is_line_marked()") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      CHECK_FALSE(board.is_line_marked(i));
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 276 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto line_num) { sum += line_num; } };
    board.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_box_marked()") {
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_FALSE(board.is_box_marked(i));
  }

  SUBCASE("for_each_player_boxmark(player_one, lambda)") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("for_each_player_boxmark(computer, lambda)") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_completed()") {
    CHECK_FALSE(board.is_completed());
  }

}

TEST_CASE("all lines marked by one player") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  Board board{ dimensions };
  for (std::size_t i{0}; i < board.get_max_lines(); ++i)
    board.mark_line(Player::ONE, i);

  SUBCASE("is_line_marked()") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      CHECK_UNARY(board.is_line_marked(i));
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto line_num) { sum += line_num; } };
    board.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_box_marked()") {
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_UNARY(board.is_box_marked(i));
  }

  SUBCASE("get_box_mark()") {
    for (std::size_t i{0}; i < num_boxes; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::ONE);
  }

  SUBCASE("for_each_player_boxmark(player_one, lambda)") {
    constexpr std::size_t expected_sum{ 36 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("for_each_player_boxmark(computer, lambda)") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_completed()") {
    CHECK_UNARY(board.is_completed());
  }

}

TEST_CASE("three boxes marked by one player") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  Board board{ dimensions };
  for (std::size_t i{0}; i < 10; ++i)
    board.mark_line(Player::ONE, i);

  SUBCASE("is_line_marked()") {
    for (std::size_t i{0}; i < 10; ++i)
      CHECK_UNARY(board.is_line_marked(i));
    for (std::size_t i{10}; i < board.get_max_lines(); ++i)
      CHECK_FALSE(board.is_line_marked(i));
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 231 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto line_num) { sum += line_num; } };
    board.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_box_marked()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_UNARY(board.is_box_marked(i));
    for (std::size_t i{3}; i < num_boxes; ++i)
      CHECK_FALSE(board.is_box_marked(i));
  }

  SUBCASE("get_box_mark()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::ONE);
  }

  SUBCASE("for_each_player_boxmark(player_one, lambda)") {
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("for_each_player_boxmark(computer, lambda)") {
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_completed()") {
    CHECK_FALSE(board.is_completed());
  }

}

TEST_CASE("six boxes marked by two players") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  Board board{ dimensions };
  for (std::size_t i{0}; i < 10; ++i)
    board.mark_line(Player::ONE, i);
  for (std::size_t i{14}; i < board.get_max_lines(); ++i)
    board.mark_line(Player::COMPUTER, i);

  SUBCASE("is_line_marked()") {
    for (std::size_t i{0}; i < 10; ++i)
      CHECK_UNARY(board.is_line_marked(i));
    for (std::size_t i{10}; i < 14; ++i)
      CHECK_FALSE(board.is_line_marked(i));
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      CHECK_UNARY(board.is_line_marked(i));
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 46 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto line_num) { sum += line_num; } };
    board.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_box_marked()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_UNARY(board.is_box_marked(i));
    for (std::size_t i{3}; i < 6; ++i)
      CHECK_FALSE(board.is_box_marked(i));
    for (std::size_t i{6}; i < num_boxes; ++i)
      CHECK_UNARY(board.is_box_marked(i));
  }

  SUBCASE("get_box_mark()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::ONE);
    for (std::size_t i{6}; i < num_boxes; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::COMPUTER);
  }

  SUBCASE("for_each_player_boxmark(player_one, lambda)") {
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("for_each_player_boxmark(computer, lambda)") {
    constexpr std::size_t expected_sum{ 21 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_completed()") {
    CHECK_FALSE(board.is_completed());
  }

}

TEST_CASE("six boxes marked by two players, with extra lines") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  Board board{ dimensions };
  for (std::size_t i{0}; i < 10; ++i)
    board.mark_line(Player::ONE, i);
  for (std::size_t i{14}; i < board.get_max_lines(); ++i)
    board.mark_line(Player::COMPUTER, i);
  board.mark_line(Player::ONE, 11);
  board.mark_line(Player::COMPUTER, 13);

  SUBCASE("is_line_marked()") {
    for (std::size_t i{0}; i < 10; ++i)
      CHECK_UNARY(board.is_line_marked(i));
    CHECK_FALSE(board.is_line_marked(10));
    CHECK_UNARY(board.is_line_marked(11));
    CHECK_FALSE(board.is_line_marked(12));
    CHECK_UNARY(board.is_line_marked(13));
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      CHECK_UNARY(board.is_line_marked(i));
  }

  SUBCASE("for_each_unmarked_line_num()") {
    constexpr std::size_t expected_sum{ 22 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto line_num) { sum += line_num; } };
    board.for_each_unmarked_line_num(add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_box_marked()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_UNARY(board.is_box_marked(i));
    for (std::size_t i{3}; i < 6; ++i)
      CHECK_FALSE(board.is_box_marked(i));
    for (std::size_t i{6}; i < num_boxes; ++i)
      CHECK_UNARY(board.is_box_marked(i));
  }

  SUBCASE("get_box_mark()") {
    for (std::size_t i{0}; i < 3; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::ONE);
    for (std::size_t i{6}; i < num_boxes; ++i)
      CHECK_EQ(board.get_box_mark(i), Player::COMPUTER);
  }

  SUBCASE("for_each_player_boxmark(player_one, lambda)") {
    constexpr std::size_t expected_sum{ 3 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("for_each_player_boxmark(computer, lambda)") {
    constexpr std::size_t expected_sum{ 21 };
    std::size_t sum{ 0 };
    auto add_to_sum{ [&sum] (auto box_num) { sum += box_num; } };
    board.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("is_completed()") {
    CHECK_FALSE(board.is_completed());
  }

}

TEST_CASE("operator<<") {

  std::stringstream out_board;

  SUBCASE("1 x 1 board, empty") {
    Board board{ 1 };
    out_board << board;
    std::string expected_board{
      u8"·   ·\n"
      u8"     \n"
      u8"·   ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("1 x 1 board, filled by one player") {
    Board board{ 1 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    out_board << board;
    std::string expected_board{
      u8"· ― ·\n"
      u8"| 1 |\n"
      u8"· ― ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("2 x 2 board, empty") {
    Board board{ 2 };
    out_board << board;
    std::string expected_board{
      u8"·   ·   ·\n"
      u8"         \n"
      u8"·   ·   ·\n"
      u8"         \n"
      u8"·   ·   ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("2 x 2 board, three boxes filled by two players") {
    Board board{ 2 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::ONE, 2);
    board.mark_line(Player::ONE, 5);
    board.mark_line(Player::ONE, 1);
    board.mark_line(Player::ONE, 4);
    board.mark_line(Player::ONE, 6);
    board.mark_line(Player::COMPUTER, 7);
    board.mark_line(Player::COMPUTER, 8);
    board.mark_line(Player::COMPUTER, 10);
    board.mark_line(Player::ONE, 3);
    out_board << board;
    std::string expected_board{
      u8"· ― · ― ·\n"
      u8"| 1 | 1 |\n"
      u8"· ― · ― ·\n"
      u8"| C |    \n"
      u8"· ― ·   ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("3 x 3 board, empty") {
    Board board{ 3 };
    out_board << board;
    std::string expected_board{
      u8"·   ·   ·   ·\n"
      u8"             \n"
      u8"·   ·   ·   ·\n"
      u8"             \n"
      u8"·   ·   ·   ·\n"
      u8"             \n"
      u8"·   ·   ·   ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("3 x 3 board, all lines marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    out_board << board;
    std::string expected_board{
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("3 x 3 board, three boxes marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    out_board << board;
    std::string expected_board{
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·\n"
      u8"             \n"
      u8"·   ·   ·   ·\n"
      u8"             \n"
      u8"·   ·   ·   ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    out_board << board;
    std::string expected_board{
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·\n"
      u8"             \n"
      u8"· ― · ― · ― ·\n"
      u8"| C | C | C |\n"
      u8"· ― · ― · ― ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players, with extra lines") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    board.mark_line(Player::ONE, 11);
    board.mark_line(Player::COMPUTER, 13);
    out_board << board;
    std::string expected_board{
      u8"· ― · ― · ― ·\n"
      u8"| 1 | 1 | 1 |\n"
      u8"· ― · ― · ― ·\n"
      u8"    |       |\n"
      u8"· ― · ― · ― ·\n"
      u8"| C | C | C |\n"
      u8"· ― · ― · ― ·"
    };
    CHECK_EQ(out_board.str(), expected_board);
  }

}

TEST_CASE("get_line_num(row_col_code)") {

  SUBCASE("1 x 1 board") {
    Board board{ 1 };
    CHECK_EQ(board.get_line_num(std::string{"AB"}), 0);
    CHECK_EQ(board.get_line_num(std::string{"BA"}), 1);
    CHECK_EQ(board.get_line_num(std::string{"BC"}), 2);
    CHECK_EQ(board.get_line_num(std::string{"CB"}), 3);
  }

  SUBCASE("2 x 2 board") {
    Board board{ 2 };
    CHECK_EQ(board.get_line_num(std::string{"AB"}), 0);
    CHECK_EQ(board.get_line_num(std::string{"AD"}), 1);
    CHECK_EQ(board.get_line_num(std::string{"BA"}), 2);
    CHECK_EQ(board.get_line_num(std::string{"BC"}), 3);
    CHECK_EQ(board.get_line_num(std::string{"BE"}), 4);
    CHECK_EQ(board.get_line_num(std::string{"CB"}), 5);
    CHECK_EQ(board.get_line_num(std::string{"CD"}), 6);
    CHECK_EQ(board.get_line_num(std::string{"DA"}), 7);
    CHECK_EQ(board.get_line_num(std::string{"DC"}), 8);
    CHECK_EQ(board.get_line_num(std::string{"DE"}), 9);
    CHECK_EQ(board.get_line_num(std::string{"EB"}), 10);
    CHECK_EQ(board.get_line_num(std::string{"ED"}), 11);
  }

  SUBCASE("3 x 3 board") {
    Board board{ 3 };
    CHECK_EQ(board.get_line_num(std::string{"AB"}), 0);
    CHECK_EQ(board.get_line_num(std::string{"AD"}), 1);
    CHECK_EQ(board.get_line_num(std::string{"AF"}), 2);
    CHECK_EQ(board.get_line_num(std::string{"BA"}), 3);
    CHECK_EQ(board.get_line_num(std::string{"BC"}), 4);
    CHECK_EQ(board.get_line_num(std::string{"BE"}), 5);
    CHECK_EQ(board.get_line_num(std::string{"BG"}), 6);
    CHECK_EQ(board.get_line_num(std::string{"CB"}), 7);
    CHECK_EQ(board.get_line_num(std::string{"CD"}), 8);
    CHECK_EQ(board.get_line_num(std::string{"CF"}), 9);
    CHECK_EQ(board.get_line_num(std::string{"DA"}), 10);
    CHECK_EQ(board.get_line_num(std::string{"DC"}), 11);
    CHECK_EQ(board.get_line_num(std::string{"DE"}), 12);
    CHECK_EQ(board.get_line_num(std::string{"DG"}), 13);
    CHECK_EQ(board.get_line_num(std::string{"EB"}), 14);
    CHECK_EQ(board.get_line_num(std::string{"ED"}), 15);
    CHECK_EQ(board.get_line_num(std::string{"EF"}), 16);
    CHECK_EQ(board.get_line_num(std::string{"FA"}), 17);
    CHECK_EQ(board.get_line_num(std::string{"FC"}), 18);
    CHECK_EQ(board.get_line_num(std::string{"FE"}), 19);
    CHECK_EQ(board.get_line_num(std::string{"FG"}), 20);
    CHECK_EQ(board.get_line_num(std::string{"GB"}), 21);
    CHECK_EQ(board.get_line_num(std::string{"GD"}), 22);
    CHECK_EQ(board.get_line_num(std::string{"GF"}), 23);
  }

}

