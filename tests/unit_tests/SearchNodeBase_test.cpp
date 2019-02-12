/*******************************************************************************
* DOCTEST CONFIG
*******************************************************************************/

#include "doctest.h"

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "CompilerUtils.hpp"
#include "ConstScore.hpp"
#include "Player.hpp"
#include "SearchNodeBase.hpp"

/*******************************************************************************
* MOCKS
*******************************************************************************/

class SNBMock : public SearchNodeBase, public std::enable_shared_from_this<SNBMock> {
public:
  SNBMock (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface) : SearchNodeBase{std::move(board), player_to_act, std::move(score_iface)} { }
  explicit SNBMock (const std::shared_ptr<SNBMock>& parent) : SearchNodeBase{parent} { }
  void mark_line_mock (Player player, std::size_t line_num) { this->mark_line(player, line_num); }
  std::optional<std::size_t> get_marked_line_mock () const { return this->get_marked_line(); }
  void add_child_mock (const std::shared_ptr<SearchNodeBase>& child) { this->add_child(child); }
// should be **protected**:
  std::shared_ptr<SearchNodeBase> create_detached_child () override { return std::make_shared<SNBMock>(this->shared_from_this()); }
};

/*******************************************************************************
* TEST CASES
*******************************************************************************/

TEST_CASE("is_terminal()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("empty board") {
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_FALSE(node.is_terminal());
  }

  SUBCASE("partially completed board") {
    for (std::size_t i{0}; i < board.get_max_lines() - 1; ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_FALSE(node.is_terminal());
  }

  SUBCASE("completed board") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_UNARY(node.is_terminal());
  }

  SUBCASE("completed board with copied node") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node_to_copy{ board, Player::ONE, scorer };
    MARK_AS_USED(node_to_copy);
    SNBMock node{ node_to_copy };
    CHECK_UNARY(node.is_terminal());
  }

}

TEST_CASE("calc_score()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("empty board") {
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_score(), 0);
  }

  SUBCASE("all lines marked by one player") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_score(), 9);
  }

  SUBCASE("three boxes marked by one player") {
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_score(), 3);
  }

  SUBCASE("six boxes marked by two players") {
    for (std::size_t i{0}; i < 10; ++i)
      board.mark_line(Player::ONE, i);
    for (std::size_t i{14}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::COMPUTER, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_score(), 0);
  }

}

TEST_CASE("calc_player_score(player)") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("empty board") {
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_player_score(Player::ONE), 0);
    CHECK_EQ(node.calc_player_score(Player::COMPUTER), 0);
  }

  SUBCASE("all lines marked by one player") {
    for (std::size_t i{0}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_EQ(node.calc_player_score(Player::ONE), 9);
    CHECK_EQ(node.calc_player_score(Player::COMPUTER), 0);
  }

}

TEST_CASE("mark_line(player, line_num)") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("all lines marked by one player") {
    for (std::size_t i{1}; i < board.get_max_lines(); ++i)
      board.mark_line(Player::ONE, i);
    SNBMock node{ board, Player::ONE, scorer };
    node.mark_line_mock(Player::ONE, 0);
    CHECK_EQ(node.calc_player_score(Player::ONE), 9);
    CHECK_EQ(node.calc_player_score(Player::COMPUTER), 0);
  }

}

TEST_CASE("get_marked_line()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("no line marked") {
    SNBMock node{ board, Player::ONE, scorer };
    CHECK_FALSE(node.get_marked_line_mock().has_value());
    CHECK_EQ(node.get_marked_line_mock(), std::nullopt);
  }

  SUBCASE("a line is marked") {
    SNBMock node{ board, Player::ONE, scorer };
    node.mark_line_mock(Player::ONE, 3);
    CHECK_UNARY(node.get_marked_line_mock().has_value());
    CHECK_EQ(node.get_marked_line_mock(), 3);
  }

}

TEST_CASE("has_parent()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_FALSE(node->has_parent());
    CHECK_UNARY(node->not_has_parent());
  }

  SUBCASE("create 3 detached children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(parent) };
    auto child_c{ std::make_shared<SNBMock>(parent) };
    CHECK_FALSE(parent->has_parent());
    CHECK_UNARY(child_a->has_parent());
    CHECK_UNARY(child_b->has_parent());
    CHECK_UNARY(child_c->has_parent());
  }

  SUBCASE("create 3 children, add them to parent") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_a);
    auto child_b{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_b);
    auto child_c{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_c);
    CHECK_FALSE(parent->has_parent());
    CHECK_UNARY(child_a->has_parent());
    CHECK_UNARY(child_b->has_parent());
    CHECK_UNARY(child_c->has_parent());
  }

}

TEST_CASE("has_children()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_FALSE(node->has_parent());
    CHECK_UNARY(node->not_has_parent());
  }

  SUBCASE("create 3 detached children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(parent) };
    auto child_c{ std::make_shared<SNBMock>(parent) };
    CHECK_FALSE(parent->has_parent());
    CHECK_UNARY(child_a->has_parent());
    CHECK_UNARY(child_b->has_parent());
    CHECK_UNARY(child_c->has_parent());
  }

  SUBCASE("create 3 children, add them to parent") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_a);
    auto child_b{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_b);
    auto child_c{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_c);
    CHECK_UNARY(parent->has_children());
    CHECK_FALSE(child_a->has_children());
    CHECK_FALSE(child_b->has_children());
    CHECK_FALSE(child_c->has_children());
  }

}

TEST_CASE("get_parent()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_FALSE(node->get_parent().has_value());
    CHECK_EQ(node->get_parent(), std::nullopt);
  }

  SUBCASE("create 3 detached children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(parent) };
    auto child_c{ std::make_shared<SNBMock>(parent) };
    CHECK_FALSE(parent->get_parent().has_value());
    CHECK_EQ(parent->get_parent(), std::nullopt);
    CHECK_UNARY(child_a->get_parent().has_value());
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_b->get_parent().has_value());
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_c->get_parent().has_value());
    CHECK_EQ(child_c->get_parent(), parent);
  }

  SUBCASE("create 3 children, add them to parent") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_a);
    auto child_b{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_b);
    auto child_c{ std::make_shared<SNBMock>(parent) };
    parent->add_child_mock(child_c);
    CHECK_FALSE(parent->get_parent().has_value());
    CHECK_EQ(parent->get_parent(), std::nullopt);
    CHECK_UNARY(child_a->get_parent().has_value());
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_b->get_parent().has_value());
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_c->get_parent().has_value());
    CHECK_EQ(child_c->get_parent(), parent);
  }

}

TEST_CASE("create_detached_child(child)") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("create 3 detached children") {
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::ONE, 1);
    board.mark_line(Player::ONE, 2);
    board.mark_line(Player::ONE, 3);
    board.mark_line(Player::ONE, 5);
    board.mark_line(Player::ONE, 7);
    board.mark_line(Player::ONE, 8);
    board.mark_line(Player::ONE, 9);
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_a->mark_line_mock(Player::ONE, 6);
    auto child_b{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_b->mark_line_mock(Player::ONE, 4);
    auto child_c{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_c->mark_line_mock(Player::ONE, 10);
    CHECK_FALSE(parent->get_parent().has_value());
    CHECK_EQ(parent->get_parent(), std::nullopt);
    CHECK_FALSE(parent->has_parent());
    CHECK_FALSE(parent->has_children());
    CHECK_EQ(parent->calc_score(), 0);
    CHECK_UNARY(child_a->get_parent().has_value());
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_a->has_parent());
    CHECK_FALSE(child_a->has_children());
    CHECK_EQ(child_a->calc_score(), 1);
    CHECK_UNARY(child_b->get_parent().has_value());
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_b->has_parent());
    CHECK_FALSE(child_b->has_children());
    CHECK_EQ(child_b->calc_score(), 2);
    CHECK_UNARY(child_c->get_parent().has_value());
    CHECK_EQ(child_c->get_parent(), parent);
    CHECK_UNARY(child_c->has_parent());
    CHECK_FALSE(child_c->has_children());
    CHECK_EQ(child_c->calc_score(), 0);
  }

  SUBCASE("create 3 detached children, add them to parent") {
    board.mark_line(Player::ONE, 0);
    board.mark_line(Player::ONE, 1);
    board.mark_line(Player::ONE, 2);
    board.mark_line(Player::ONE, 3);
    board.mark_line(Player::ONE, 5);
    board.mark_line(Player::ONE, 7);
    board.mark_line(Player::ONE, 8);
    board.mark_line(Player::ONE, 9);
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_a->mark_line_mock(Player::ONE, 6);
    parent->add_child_mock(child_a);
    auto child_b{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_b->mark_line_mock(Player::ONE, 4);
    parent->add_child_mock(child_b);
    auto child_c{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    child_c->mark_line_mock(Player::ONE, 10);
    parent->add_child_mock(child_c);
    CHECK_FALSE(parent->get_parent().has_value());
    CHECK_EQ(parent->get_parent(), std::nullopt);
    CHECK_FALSE(parent->has_parent());
    CHECK_UNARY(parent->has_children());
    CHECK_EQ(parent->calc_score(), 0);
    CHECK_UNARY(child_a->get_parent().has_value());
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_a->has_parent());
    CHECK_FALSE(child_a->has_children());
    CHECK_EQ(child_a->calc_score(), 1);
    CHECK_UNARY(child_b->get_parent().has_value());
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_b->has_parent());
    CHECK_FALSE(child_b->has_children());
    CHECK_EQ(child_b->calc_score(), 2);
    CHECK_UNARY(child_c->get_parent().has_value());
    CHECK_EQ(child_c->get_parent(), parent);
    CHECK_UNARY(child_c->has_parent());
    CHECK_FALSE(child_c->has_children());
    CHECK_EQ(child_c->calc_score(), 0);
  }

}

TEST_CASE("get_depth()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_EQ(node->get_depth(), 0);
  }

  SUBCASE("parent with child, grandchild, great-grandchild") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(child_a) };
    auto child_c{ std::make_shared<SNBMock>(child_b) };
    CHECK_EQ(parent->get_depth(), 0);
    CHECK_EQ(child_a->get_depth(), 1);
    CHECK_EQ(child_b->get_depth(), 2);
    CHECK_EQ(child_c->get_depth(), 3);
  }

}

TEST_CASE("get_player_to_act()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_EQ(node->get_player_to_act(), Player::ONE);
  }

  SUBCASE("parent with child, grandchild, great-grandchild") {
    auto parent{ std::make_shared<SNBMock>(board, Player::COMPUTER, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(child_a) };
    auto child_c{ std::make_shared<SNBMock>(child_b) };
    CHECK_EQ(parent->get_player_to_act(), Player::COMPUTER);
    CHECK_EQ(child_a->get_player_to_act(), Player::ONE);
    CHECK_EQ(child_b->get_player_to_act(), Player::COMPUTER);
    CHECK_EQ(child_c->get_player_to_act(), Player::ONE);
  }

}

