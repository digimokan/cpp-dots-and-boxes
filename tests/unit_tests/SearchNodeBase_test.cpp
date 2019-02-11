/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "ConstScore.hpp"
#include "Player.hpp"
#include "SearchNodeBase.hpp"

/*******************************************************************************
* MOCKS
*******************************************************************************/

class SNBMock : public SearchNodeBase {
public:
  SNBMock (Board board, std::shared_ptr<ScoreIface> score_iface) : SearchNodeBase{std::move(board), std::move(score_iface)} { }
};

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("is_terminal()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("empty board") {
    SNBMock node{ board, scorer };
    CHECK_FALSE(node.is_terminal());
  }

  SUBCASE("partially completed board") {
    for (std::size_t i{0}; i < board.get_max_lines() - 1; ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, scorer };
    CHECK_FALSE(node.is_terminal());
  }

  SUBCASE("completed board") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, scorer };
    CHECK_UNARY(node.is_terminal());
  }

  SUBCASE("completed board with copied node") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node_to_copy{ board, scorer };
    SNBMock node{ node_to_copy };
    CHECK_UNARY(node.is_terminal());
  }

}

