/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

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

