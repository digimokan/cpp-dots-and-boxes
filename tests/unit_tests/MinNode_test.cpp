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

TEST_CASE("get_alpha_or_beta(), set_alpha_or_beta()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto node{ std::make_shared<MinNode>(board, Player::ONE, scorer) };

  SUBCASE("beta not set") {
    CHECK_EQ(node->get_alpha_or_beta(), std::nullopt);
  }

  SUBCASE("initial beta set") {
    node->set_alpha_or_beta(4);
    const std::optional<int64_t> beta{ node->get_alpha_or_beta() };
    CHECK_UNARY(beta.has_value());
    CHECK_EQ(beta, 4);
  }

  SUBCASE("replace with lower score") {
    node->set_alpha_or_beta(4);
    node->set_alpha_or_beta(2);
    const std::optional<int64_t> beta{ node->get_alpha_or_beta() };
    CHECK_UNARY(beta.has_value());
    CHECK_EQ(beta, 2);
  }

  SUBCASE("do not replace with higher score") {
    node->set_alpha_or_beta(4);
    node->set_alpha_or_beta(8);
    const std::optional<int64_t> beta{ node->get_alpha_or_beta() };
    CHECK_UNARY(beta.has_value());
    CHECK_EQ(beta, 4);
  }

}

TEST_CASE("cutoff_gen_children()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto single_node{ std::make_shared<MinNode>(board, Player::ONE, scorer) };
  auto parent{ std::make_shared<MaxNode>(board, Player::ONE, scorer) };
  auto node_with_parent_children{ std::make_shared<MinNode>(parent) };
  auto child{ std::make_shared<MaxNode>(node_with_parent_children) };
  auto node_with_parent{ std::make_shared<MinNode>(parent) };
  auto node_with_children{ std::make_shared<MinNode>(board, Player::ONE, scorer) };
  auto alt_child{ std::make_shared<MaxNode>(node_with_children) };

  SUBCASE("node with no parent, no children, no beta") {
    CHECK_FALSE(single_node->cutoff_gen_children());
  }

  SUBCASE("node with no parent, no children, beta") {
    single_node->set_alpha_or_beta(4);
    CHECK_FALSE(single_node->cutoff_gen_children());
  }

  SUBCASE("node with no parent, children, no beta") {
    CHECK_FALSE(node_with_children->cutoff_gen_children());
  }

  SUBCASE("node with no parent, children, beta") {
    node_with_children->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (no alpha), no children, no beta") {
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (has alpha), no children, no beta") {
    parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (no alpha), no children, beta") {
    node_with_parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (larger alpha), no children, beta") {
    node_with_parent->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(8);
    CHECK_UNARY(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (smaller alpha), no children, beta") {
    node_with_parent->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(2);
    CHECK_FALSE(node_with_parent->cutoff_gen_children());
  }

  SUBCASE("node with parent (no alpha), children, no beta") {
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (has alpha), children, no beta") {
    node_with_parent->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (no alpha), children, beta") {
    node_with_parent_children->set_alpha_or_beta(4);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (larger alpha), children, beta") {
    node_with_parent_children->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(8);
    CHECK_UNARY(node_with_parent_children->cutoff_gen_children());
  }

  SUBCASE("node with parent (smaller alpha), children, beta") {
    node_with_parent_children->set_alpha_or_beta(4);
    parent->set_alpha_or_beta(2);
    CHECK_FALSE(node_with_parent_children->cutoff_gen_children());
  }

}

