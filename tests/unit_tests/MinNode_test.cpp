/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <algorithm>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "ConstScore.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("3 x 3 board, multiple scoring opportunities") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  board.mark_line(Player::COMPUTER, 0);
  board.mark_line(Player::COMPUTER, 1);
  board.mark_line(Player::COMPUTER, 2);
  board.mark_line(Player::COMPUTER, 3);
  board.mark_line(Player::COMPUTER, 5);
  board.mark_line(Player::COMPUTER, 7);
  board.mark_line(Player::COMPUTER, 8);
  board.mark_line(Player::COMPUTER, 9);
  auto parent{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
  std::list<std::shared_ptr<SearchNodeIface>> children;
  std::list<std::shared_ptr<SearchNodeIface>> grandchildren;
  auto collect_child = [&children] (auto child) { children.push_back(child); };
  auto collect_grandchild = [&grandchildren] (auto child) { grandchildren.push_back(child); };

  SUBCASE("gens correct number of children") {
    parent->gen_children(collect_child);
    CHECK_EQ(children.size(), 16);
  }

  SUBCASE("calculates correct min score from children") {
    parent->gen_children(collect_child);
    auto setmm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), setmm);
    parent->set_minimax_score_from_children();
    CHECK_EQ(parent->get_minimax_score(), -2);
  }

  SUBCASE("creates correct Max child (that has the min score)") {
    parent->gen_children(collect_child);
    auto set_children_mm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), set_children_mm);
    parent->set_minimax_score_from_children();
    auto find_min_child = [] (auto node) { return (node->get_minimax_score() == -2); };
    auto min_child{ std::find_if(children.begin(), children.end(), find_min_child) };
    CHECK_NE(min_child, children.end());
    CHECK_EQ((*min_child)->get_minimax_score(), -2);
  }

  SUBCASE("Max child performs correctly") {
    parent->gen_children(collect_child);
    auto set_children_mm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), set_children_mm);
    parent->set_minimax_score_from_children();
    auto find_min_child = [] (auto node) { return (node->get_minimax_score() == -2); };
    auto min_child{ std::find_if(children.begin(), children.end(), find_min_child) };
    auto mc{ *min_child };
    mc->gen_children(collect_grandchild);
    std::for_each(grandchildren.begin(), grandchildren.end(), set_children_mm);
    mc->set_minimax_score_from_children();
    CHECK_EQ(mc->get_minimax_score(), -1);
  }

}

