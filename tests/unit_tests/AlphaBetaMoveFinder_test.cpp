/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "AlphaBetaMoveFinder.hpp"
#include "ConstScore.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("1 x 1 board") {

  constexpr std::size_t max_search_depth{ 10 };
  constexpr std::size_t dimensions{ 1 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  AlphaBetaMoveFinder finder{};

  SUBCASE("COMPUTER to make move #2") {
    board.mark_line(Player::ONE, 0);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 1);
  }

  SUBCASE("COMPUTER to make move #4") {
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), -1);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 1);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 3);
  }

}

TEST_CASE("2 x 2 board") {

  constexpr std::size_t dimensions{ 2 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  AlphaBetaMoveFinder finder{};

  SUBCASE("COMPUTER to make move #2, max search depth 3") {
    constexpr std::size_t max_search_depth{ 3 };
    board.mark_line(Player::ONE, 0);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 1);
  }

  SUBCASE("COMPUTER to make move #4, max search depth 1") {
    constexpr std::size_t max_search_depth{ 1 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 3);
  }

  SUBCASE("COMPUTER to make move #4, max search depth 3") {
    constexpr std::size_t max_search_depth{ 3 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 4);
  }

  SUBCASE("COMPUTER to make move #4, max search depth 5") {
    constexpr std::size_t max_search_depth{ 5 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 4);
  }

}

TEST_CASE("3 x 3 board") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  AlphaBetaMoveFinder finder{};

  SUBCASE("COMPUTER to make move #4, max search depth 3") {
    constexpr std::size_t max_search_depth{ 3 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 3);
  }

}

TEST_CASE("4 x 4 board") {

  constexpr std::size_t dimensions{ 4 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  AlphaBetaMoveFinder finder{};

  SUBCASE("COMPUTER to make move #4, max search depth 2") {
    constexpr std::size_t max_search_depth{ 2 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 3);
  }

}

TEST_CASE("5 x 5 board") {

  constexpr std::size_t dimensions{ 5 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  AlphaBetaMoveFinder finder{};

  SUBCASE("COMPUTER to make move #4, max search depth 2") {
    constexpr std::size_t max_search_depth{ 2 };
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::COMPUTER, 1);
    board.mark_line(Player::ONE, 2);
    auto move_1{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
    auto comp_move{ finder.find_best_move(move_1, max_search_depth) };
    CHECK_EQ(comp_move->calc_score(), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::ONE), 0);
    CHECK_EQ(comp_move->calc_player_score(Player::COMPUTER), 0);
    CHECK_EQ(comp_move->get_player_to_act(), Player::ONE);
    CHECK_UNARY(comp_move->get_marked_line().has_value());
    CHECK_EQ(comp_move->get_marked_line().value(), 3);
  }

}

