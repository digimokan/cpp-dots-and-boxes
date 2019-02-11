/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include "RandomBoxScore.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("calc_score(board)") {


  SUBCASE("1 x 1 board, empty") {
    constexpr std::size_t dimensions{ 1 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    const int64_t expected_score{ 0 };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("1 x 1 board, filled by one player") {
    constexpr std::size_t dimensions{ 1 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    const int64_t expected_score{ scorer.get_random_box_score(0) };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("2 x 2 board, empty") {
    constexpr std::size_t dimensions{ 2 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    const int64_t expected_score{ 0 };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("2 x 2 board, three boxes filled by two players") {
    constexpr std::size_t dimensions{ 2 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
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
    const int64_t expected_score{
      scorer.get_random_box_score(0) + scorer.get_random_box_score(1)
      - scorer.get_random_box_score(2)
    };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("3 x 3 board, empty") {
    constexpr std::size_t dimensions{ 3 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    const int64_t expected_score{ 0 };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("3 x 3 board, all lines marked by one player") {
    constexpr std::size_t dimensions{ 3 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    const int64_t expected_score{
      scorer.get_random_box_score(0) + scorer.get_random_box_score(1) + scorer.get_random_box_score(2)
      + scorer.get_random_box_score(3) + scorer.get_random_box_score(4) + scorer.get_random_box_score(5)
      + scorer.get_random_box_score(6) + scorer.get_random_box_score(7) + scorer.get_random_box_score(8)
    };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("3 x 3 board, three boxes marked by one player") {
    constexpr std::size_t dimensions{ 3 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    const int64_t expected_score{
      scorer.get_random_box_score(0) + scorer.get_random_box_score(1) + scorer.get_random_box_score(2)
    };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players") {
    constexpr std::size_t dimensions{ 3 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    const int64_t expected_score{
      scorer.get_random_box_score(0) + scorer.get_random_box_score(1) + scorer.get_random_box_score(2)
      - scorer.get_random_box_score(6) - scorer.get_random_box_score(7) - scorer.get_random_box_score(8)
    };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

  SUBCASE("3 x 3 board, six boxes marked by two players, with extra lines") {
    constexpr std::size_t dimensions{ 3 };
    RandomBoxScore scorer{ dimensions };
    Board board{ dimensions };
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    board.mark_line(Player::ONE, 11);
    board.mark_line(Player::COMPUTER, 13);
    const int64_t expected_score{
      scorer.get_random_box_score(0) + scorer.get_random_box_score(1) + scorer.get_random_box_score(2)
      - scorer.get_random_box_score(6) - scorer.get_random_box_score(7) - scorer.get_random_box_score(8)
    };
    CHECK_EQ(scorer.calc_score(board), expected_score);
  }

}

