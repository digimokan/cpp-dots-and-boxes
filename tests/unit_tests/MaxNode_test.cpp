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
#include "MaxNode.hpp"
#include "MinNode.hpp"

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("3 x 3 board, multiple scoring opportunities") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  board.mark_line(Player::ONE, 0);
  board.mark_line(Player::ONE, 1);
  board.mark_line(Player::ONE, 2);
  board.mark_line(Player::ONE, 3);
  board.mark_line(Player::ONE, 5);
  board.mark_line(Player::ONE, 7);
  board.mark_line(Player::ONE, 8);
  board.mark_line(Player::ONE, 9);
  auto parent{ std::make_shared<MaxNode>(board, Player::ONE, scorer) };
  std::list<std::shared_ptr<SearchNodeIface>> children;
  std::list<std::shared_ptr<SearchNodeIface>> grandchildren;
  auto collect_child = [&children] (auto child) { children.push_back(child); };
  auto collect_grandchild = [&grandchildren] (auto child) { grandchildren.push_back(child); };

  SUBCASE("gens correct number of children") {
    parent->gen_children(collect_child);
    CHECK_EQ(children.size(), 16);
  }

  SUBCASE("calculates correct max score from children") {
    parent->gen_children(collect_child);
    auto setmm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), setmm);
    parent->set_minimax_score_from_children();
    CHECK_EQ(parent->get_minimax_score(), 2);
  }

  SUBCASE("creates correct Min child (that has the max score)") {
    parent->gen_children(collect_child);
    auto set_children_mm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), set_children_mm);
    parent->set_minimax_score_from_children();
    auto find_max_child = [] (auto node) { return (node->get_minimax_score() == 2); };
    auto max_child{ std::find_if(children.begin(), children.end(), find_max_child) };
    CHECK_NE(max_child, children.end());
    CHECK_EQ((*max_child)->get_minimax_score(), 2);
  }

  SUBCASE("Min child performs correctly") {
    parent->gen_children(collect_child);
    auto set_children_mm = [] (auto node) { node->set_minimax_score(); };
    std::for_each(children.begin(), children.end(), set_children_mm);
    parent->set_minimax_score_from_children();
    auto find_max_child = [] (auto node) { return (node->get_minimax_score() == 2); };
    auto max_child{ std::find_if(children.begin(), children.end(), find_max_child) };
    auto mc{ *max_child };
    mc->gen_children(collect_grandchild);
    std::for_each(grandchildren.begin(), grandchildren.end(), set_children_mm);
    mc->set_minimax_score_from_children();
    CHECK_EQ(mc->get_minimax_score(), 1);
  }

}

TEST_CASE("get_alpha_or_beta(), set_alpha_or_beta()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto node{ std::make_shared<MaxNode>(board, Player::ONE, scorer) };

  SUBCASE("alpha not set") {
    CHECK_EQ(node->get_alpha_or_beta(), std::nullopt);
  }

  SUBCASE("initial alpha set") {
    node->set_alpha_or_beta(4);
    const std::optional<int64_t> alpha{ node->get_alpha_or_beta() };
    CHECK_UNARY(alpha.has_value());
    CHECK_EQ(alpha, 4);
  }

  SUBCASE("replace with higher score") {
    node->set_alpha_or_beta(4);
    node->set_alpha_or_beta(8);
    const std::optional<int64_t> alpha{ node->get_alpha_or_beta() };
    CHECK_UNARY(alpha.has_value());
    CHECK_EQ(alpha, 8);
  }

  SUBCASE("do not replace with lower score") {
    node->set_alpha_or_beta(4);
    node->set_alpha_or_beta(2);
    const std::optional<int64_t> alpha{ node->get_alpha_or_beta() };
    CHECK_UNARY(alpha.has_value());
    CHECK_EQ(alpha, 4);
  }

}

TEST_CASE("cutoff_gen_children()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto single_node{ std::make_shared<MaxNode>(board, Player::COMPUTER, scorer) };
  auto parent{ std::make_shared<MinNode>(board, Player::COMPUTER, scorer) };
  auto node_with_parent_children{ std::make_shared<MaxNode>(parent) };
  auto child{ std::make_shared<MinNode>(node_with_parent_children) };
  auto node_with_parent{ std::make_shared<MaxNode>(parent) };
  auto node_with_children{ std::make_shared<MaxNode>(board, Player::COMPUTER, scorer) };
  auto alt_child{ std::make_shared<MinNode>(node_with_children) };

  SUBCASE("node with no parent, no children, no alpha") {
    CHECK_FALSE(single_node->cutoff_gen_children());
  }

  SUBCASE("node with no parent, no children, alpha") {
    single_node->set_alpha_or_beta(4);
    CHECK_FALSE(single_node->cutoff_gen_children());
  }

  SUBCASE("node with no parent, children, no alpha") {
    CHECK_FALSE(node_with_children->cutoff_gen_children());
  }

  SUBCASE("node with no parent, children, alpha") {
    node_with_children->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (no alpha), no children, no alpha") {
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (has beta), no children, no alpha") {
    parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (no beta), no children, alpha") {
    node_with_parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (larger beta), no children, alpha") {
    node_with_parent->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(8);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (smaller beta), no children, alpha") {
    node_with_parent->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(2);
    CHECK_UNARY(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (no beta), children, no alpha") {
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (has beta), children, no alpha") {
    node_with_parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (no beta), children, alpha") {
    node_with_parent_children->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (larger beta), children, alpha") {
    node_with_parent_children->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(8);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (smaller beta), children, alpha") {
    node_with_parent_children->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(2);
    CHECK_UNARY(node_with_parent_children->cutoff_gen_children());
  }

}

