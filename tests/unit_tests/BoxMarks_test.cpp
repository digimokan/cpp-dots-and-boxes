/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"
#include "Player.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("empty BoxMarks for various board sizes") {

  SUBCASE("1 x 1 Board") {
    constexpr std::size_t dimensions{ 1 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (auto box_num) { sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
    sum = 0;
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("2 x 2 Board") {
    constexpr std::size_t dimensions{ 2 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (auto box_num) { sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
    sum = 0;
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("3 x 3 Board") {
    constexpr std::size_t dimensions{ 3 };
    BoxMarks box_marks{ dimensions };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (auto box_num) { sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
    sum = 0;
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

  SUBCASE("copied 3 x 3 Board") {
    constexpr std::size_t dimensions{ 3 };
    BoxMarks box_marks_to_copy{ dimensions };
    BoxMarks box_marks{ box_marks_to_copy };
    for (std::size_t i = 0; i < (dimensions * dimensions); ++i) {
      CHECK_FALSE(box_marks.is_marked(i));
      CHECK_UNARY(box_marks.not_marked(i));
    }
    CHECK_EQ(box_marks.get_board_dimensions(), dimensions);
    CHECK_EQ(box_marks.get_num_boxes(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_unmarked(), dimensions * dimensions);
    CHECK_EQ(box_marks.get_num_marked(), 0);
    CHECK_FALSE(box_marks.all_marked());
    constexpr std::size_t expected_sum{ 0 };
    std::size_t sum{ 0 };
    auto add_to_sum = [&sum] (auto box_num) { sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_sum);
    CHECK_EQ(sum, expected_sum);
    sum = 0;
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_sum);
    CHECK_EQ(sum, expected_sum);
  }

}

TEST_CASE("all boxes marked by one player") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  BoxMarks box_marks_to_copy{ dimensions };
  for (std::size_t i = 1; i < num_boxes; ++i)
    box_marks_to_copy.mark(i, Player::ONE);
  BoxMarks box_marks{ box_marks_to_copy };
  box_marks.mark(0, Player::ONE);

  SUBCASE("is_marked()") {
    for (std::size_t i = 0; i < num_boxes; ++i)
      CHECK_UNARY(box_marks.is_marked(i));
  }

  SUBCASE("not_marked()") {
    for (std::size_t i = 0; i < num_boxes; ++i)
      CHECK_FALSE(box_marks.not_marked(i));
  }

  SUBCASE("get_num_unmarked()") {
    CHECK_EQ(box_marks.get_num_unmarked(), 0);
  }

  SUBCASE("get_num_marked()") {
    CHECK_EQ(box_marks.get_num_marked(), num_boxes);
  }

  SUBCASE("all_marked()") {
    CHECK_UNARY(box_marks.all_marked());
  }

  SUBCASE("for_each_player_boxmark()") {
    constexpr std::size_t expected_playerone_sum{ 36 };
    constexpr std::size_t expected_computer_sum{ 0 };
    std::size_t playerone_sum{ 0 };
    auto add_to_playerone_sum = [&playerone_sum] (auto box_num) { playerone_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_playerone_sum);
    CHECK_EQ(playerone_sum, expected_playerone_sum);
    std::size_t computer_sum{ 0 };
    auto add_to_computer_sum = [&computer_sum] (auto box_num) { computer_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_computer_sum);
    CHECK_EQ(computer_sum, expected_computer_sum);
  }

}

TEST_CASE("all boxes marked by two players") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  BoxMarks box_marks{ dimensions };
  for (std::size_t i = 0; i < 5; ++i)
    box_marks.mark(i, Player::ONE);
  for (std::size_t i = 5; i < num_boxes; ++i)
    box_marks.mark(i, Player::COMPUTER);

  SUBCASE("is_marked()") {
    for (std::size_t i = 0; i < num_boxes; ++i)
      CHECK_UNARY(box_marks.is_marked(i));
  }

  SUBCASE("not_marked()") {
    for (std::size_t i = 0; i < num_boxes; ++i)
      CHECK_FALSE(box_marks.not_marked(i));
  }

  SUBCASE("get_num_unmarked()") {
    CHECK_EQ(box_marks.get_num_unmarked(), 0);
  }

  SUBCASE("get_num_marked()") {
    CHECK_EQ(box_marks.get_num_marked(), num_boxes);
  }

  SUBCASE("all_marked()") {
    CHECK_UNARY(box_marks.all_marked());
  }

  SUBCASE("for_each_player_boxmark()") {
    constexpr std::size_t expected_playerone_sum{ 10 };
    constexpr std::size_t expected_computer_sum{ 26 };
    std::size_t playerone_sum{ 0 };
    auto add_to_playerone_sum = [&playerone_sum] (auto box_num) { playerone_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_playerone_sum);
    CHECK_EQ(playerone_sum, expected_playerone_sum);
    std::size_t computer_sum{ 0 };
    auto add_to_computer_sum = [&computer_sum] (auto box_num) { computer_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_computer_sum);
    CHECK_EQ(computer_sum, expected_computer_sum);
  }

}

TEST_CASE("some boxes marked by two players") {

  constexpr std::size_t dimensions{ 3 };
  constexpr std::size_t num_boxes{ dimensions * dimensions };
  BoxMarks box_marks{ dimensions };
  box_marks.mark(0, Player::ONE);
  box_marks.mark(1, Player::ONE);
  box_marks.mark(2, Player::ONE);
  box_marks.mark(3, Player::COMPUTER);
  box_marks.mark(4, Player::COMPUTER);
  box_marks.mark(5, Player::COMPUTER);

  SUBCASE("is_marked()") {
    for (std::size_t i = 0; i < 5; ++i)
      CHECK_UNARY(box_marks.is_marked(i));
    for (std::size_t i = 6; i < num_boxes; ++i)
      CHECK_FALSE(box_marks.is_marked(i));
  }

  SUBCASE("not_marked()") {
    for (std::size_t i = 0; i < 5; ++i)
      CHECK_FALSE(box_marks.not_marked(i));
    for (std::size_t i = 6; i < num_boxes; ++i)
      CHECK_UNARY(box_marks.not_marked(i));
  }

  SUBCASE("get_num_unmarked()") {
    CHECK_EQ(box_marks.get_num_unmarked(), 3);
  }

  SUBCASE("get_num_marked()") {
    CHECK_EQ(box_marks.get_num_marked(), 6);
  }

  SUBCASE("all_marked()") {
    CHECK_FALSE(box_marks.all_marked());
  }

  SUBCASE("for_each_player_boxmark()") {
    constexpr std::size_t expected_playerone_sum{ 3 };
    constexpr std::size_t expected_computer_sum{ 12 };
    std::size_t playerone_sum{ 0 };
    auto add_to_playerone_sum = [&playerone_sum] (auto box_num) { playerone_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::ONE, add_to_playerone_sum);
    CHECK_EQ(playerone_sum, expected_playerone_sum);
    std::size_t computer_sum{ 0 };
    auto add_to_computer_sum = [&computer_sum] (auto box_num) { computer_sum += box_num; };
    box_marks.for_each_player_boxmark(Player::COMPUTER, add_to_computer_sum);
    CHECK_EQ(computer_sum, expected_computer_sum);
  }

}

