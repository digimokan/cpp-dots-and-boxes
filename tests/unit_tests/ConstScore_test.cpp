/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "ConstScore.hpp"
#include "Player.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("calc_score(board)") {

  ConstScore scorer{};

  SUBCASE("1 x 1 board, empty") {
    Board board{ 1 };
    CHECK_EQ(scorer.calc_score(board), 0);
  }

  SUBCASE("1 x 1 board, filled by one player") {
    Board board{ 1 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_score(board), 1);
  }

  SUBCASE("2 x 2 board, empty") {
    Board board{ 2 };
    CHECK_EQ(scorer.calc_score(board), 0);
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
    CHECK_EQ(scorer.calc_score(board), 1);
  }

  SUBCASE("3 x 3 board, empty") {
    Board board{ 3 };
    CHECK_EQ(scorer.calc_score(board), 0);
  }

  SUBCASE("3 x 3 board, all lines marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_score(board), 9);
  }

  SUBCASE("3 x 3 board, three boxes marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_score(board), 3);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    CHECK_EQ(scorer.calc_score(board), 0);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players, with extra lines") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    board.mark_line(Player::ONE, 11);
    board.mark_line(Player::COMPUTER, 13);
    CHECK_EQ(scorer.calc_score(board), 0);
  }

}

TEST_CASE("calc_player_score(player, board)") {

  ConstScore scorer{};

  SUBCASE("1 x 1 board, empty") {
    Board board{ 1 };
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 0);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
  }

  SUBCASE("1 x 1 board, filled by one player") {
    Board board{ 1 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 1);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
  }

  SUBCASE("2 x 2 board, empty") {
    Board board{ 2 };
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 0);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
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
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 2);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 1);
  }

  SUBCASE("3 x 3 board, empty") {
    Board board{ 3 };
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 0);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
  }

  SUBCASE("3 x 3 board, all lines marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 9);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
  }

  SUBCASE("3 x 3 board, three boxes marked by one player") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 3);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 0);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 3);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 3);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players, with extra lines") {
    Board board{ 3 };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    board.mark_line(Player::ONE, 11);
    board.mark_line(Player::COMPUTER, 13);
    CHECK_EQ(scorer.calc_player_score(Player::ONE, board), 3);
    CHECK_EQ(scorer.calc_player_score(Player::COMPUTER, board), 3);
  }

}

