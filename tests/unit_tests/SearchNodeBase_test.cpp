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
  void add_child_mock (const std::shared_ptr<SearchNodeBase>& child) { this->add_child(child); }
  std::shared_ptr<SearchNodeBase> get_max_child_mock () const { return this->get_max_child(); }
  std::shared_ptr<SearchNodeBase> get_min_child_mock () const { return this->get_min_child(); }
  std::shared_ptr<SearchNodeIface> get_minimax_child () override { return this->get_max_child(); }
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
    CHECK_FALSE(node.get_marked_line().has_value());
    CHECK_EQ(node.get_marked_line(), std::nullopt);
  }

  SUBCASE("a line is marked") {
    SNBMock node{ board, Player::ONE, scorer };
    node.mark_line_mock(Player::ONE, 3);
    CHECK_UNARY(node.get_marked_line().has_value());
    CHECK_EQ(node.get_marked_line(), 3);
  }

}

TEST_CASE("has_parent()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };

  SUBCASE("single node") {
    auto node{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    CHECK_FALSE(node->has_parent());
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
    CHECK_FALSE(node->has_children());
  }

  SUBCASE("create 3 detached children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(parent) };
    auto child_c{ std::make_shared<SNBMock>(parent) };
    CHECK_FALSE(parent->has_children());
    CHECK_FALSE(child_a->has_children());
    CHECK_FALSE(child_b->has_children());
    CHECK_FALSE(child_c->has_children());
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

  SUBCASE("create 3 detached children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto child_a{ std::make_shared<SNBMock>(parent) };
    auto child_b{ std::make_shared<SNBMock>(parent) };
    auto child_c{ std::make_shared<SNBMock>(parent) };
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_EQ(child_b->get_parent(), parent);
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
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_EQ(child_b->get_parent(), parent);
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
    CHECK_FALSE(parent->has_parent());
    CHECK_FALSE(parent->has_children());
    CHECK_EQ(parent->calc_score(), 0);
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_a->has_parent());
    CHECK_FALSE(child_a->has_children());
    CHECK_EQ(child_a->calc_score(), 1);
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_b->has_parent());
    CHECK_FALSE(child_b->has_children());
    CHECK_EQ(child_b->calc_score(), 2);
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
    CHECK_FALSE(parent->has_parent());
    CHECK_UNARY(parent->has_children());
    CHECK_EQ(parent->calc_score(), 0);
    CHECK_EQ(child_a->get_parent(), parent);
    CHECK_UNARY(child_a->has_parent());
    CHECK_FALSE(child_a->has_children());
    CHECK_EQ(child_a->calc_score(), 1);
    CHECK_EQ(child_b->get_parent(), parent);
    CHECK_UNARY(child_b->has_parent());
    CHECK_FALSE(child_b->has_children());
    CHECK_EQ(child_b->calc_score(), 2);
    CHECK_EQ(child_c->get_parent(), parent);
    CHECK_UNARY(child_c->has_parent());
    CHECK_FALSE(child_c->has_children());
    CHECK_EQ(child_c->calc_score(), 0);
  }

}

TEST_CASE("get_max_child(), get_min_child()") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
  Board board_a{ dimensions };
  board_a.mark_line(Player::ONE, 0);
  board_a.mark_line(Player::ONE, 2);
  board_a.mark_line(Player::ONE, 3);
  auto child_a{ std::make_shared<SNBMock>(board_a, Player::ONE, scorer) };
  child_a->set_minimax_score();
  Board board_b{ dimensions };
  board_b.mark_line(Player::ONE, 0);
  board_b.mark_line(Player::ONE, 1);
  board_b.mark_line(Player::ONE, 2);
  board_b.mark_line(Player::ONE, 3);
  board_b.mark_line(Player::ONE, 4);
  board_b.mark_line(Player::ONE, 5);
  board_b.mark_line(Player::ONE, 6);
  board_b.mark_line(Player::ONE, 7);
  board_b.mark_line(Player::ONE, 8);
  board_b.mark_line(Player::ONE, 9);
  board_b.mark_line(Player::ONE, 10);
  board_b.mark_line(Player::ONE, 11);
  auto child_b{ std::make_shared<SNBMock>(board_b, Player::ONE, scorer) };
  child_b->set_minimax_score();
  Board board_c{ dimensions };
  board_c.mark_line(Player::ONE, 5);
  board_c.mark_line(Player::ONE, 6);
  board_c.mark_line(Player::ONE, 7);
  board_c.mark_line(Player::ONE, 8);
  board_c.mark_line(Player::ONE, 9);
  board_c.mark_line(Player::ONE, 10);
  board_c.mark_line(Player::ONE, 11);
  auto child_c{ std::make_shared<SNBMock>(board_c, Player::ONE, scorer) };
  child_c->set_minimax_score();
  parent->add_child_mock(child_a);
  parent->add_child_mock(child_b);
  parent->add_child_mock(child_c);

  SUBCASE("max of three children") {
    auto max_child{ parent->get_max_child_mock() };
    CHECK_EQ(max_child, child_b);
  }

  SUBCASE("min of three children") {
    auto min_child{ parent->get_min_child_mock() };
    CHECK_EQ(min_child, child_a);
  }

}

TEST_CASE("set_minimax_score_from_children()") {

  constexpr std::size_t dimensions{ 2 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
  Board board_a{ dimensions };
  board_a.mark_line(Player::ONE, 0);
  board_a.mark_line(Player::ONE, 2);
  board_a.mark_line(Player::ONE, 3);
  auto child_a{ std::make_shared<SNBMock>(board_a, Player::ONE, scorer) };
  child_a->set_minimax_score();
  Board board_b{ dimensions };
  board_b.mark_line(Player::ONE, 0);
  board_b.mark_line(Player::ONE, 1);
  board_b.mark_line(Player::ONE, 2);
  board_b.mark_line(Player::ONE, 3);
  board_b.mark_line(Player::ONE, 4);
  board_b.mark_line(Player::ONE, 5);
  board_b.mark_line(Player::ONE, 6);
  board_b.mark_line(Player::ONE, 7);
  board_b.mark_line(Player::ONE, 8);
  board_b.mark_line(Player::ONE, 9);
  board_b.mark_line(Player::ONE, 10);
  board_b.mark_line(Player::ONE, 11);
  auto child_b{ std::make_shared<SNBMock>(board_b, Player::ONE, scorer) };
  child_b->set_minimax_score();
  Board board_c{ dimensions };
  board_c.mark_line(Player::ONE, 5);
  board_c.mark_line(Player::ONE, 6);
  board_c.mark_line(Player::ONE, 7);
  board_c.mark_line(Player::ONE, 8);
  board_c.mark_line(Player::ONE, 9);
  board_c.mark_line(Player::ONE, 10);
  board_c.mark_line(Player::ONE, 11);
  auto child_c{ std::make_shared<SNBMock>(board_c, Player::ONE, scorer) };
  child_c->set_minimax_score();
  parent->add_child_mock(child_a);
  parent->add_child_mock(child_b);
  parent->add_child_mock(child_c);

  SUBCASE("max of three children") {
    parent->set_minimax_score_from_children();
    CHECK_EQ(parent->get_minimax_score(), 4);
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
    auto child_a{ std::dynamic_pointer_cast<SNBMock>(parent->create_detached_child()) };
    auto child_b{ std::dynamic_pointer_cast<SNBMock>(child_a->create_detached_child()) };
    auto child_c{ std::dynamic_pointer_cast<SNBMock>(child_b->create_detached_child()) };
    CHECK_EQ(parent->get_player_to_act(), Player::COMPUTER);
    CHECK_EQ(child_a->get_player_to_act(), Player::ONE);
    CHECK_EQ(child_b->get_player_to_act(), Player::COMPUTER);
    CHECK_EQ(child_c->get_player_to_act(), Player::ONE);
  }

}

TEST_CASE("gen_children(act_on_child)") {

  constexpr std::size_t dimensions{ 3 };
  auto scorer{ std::make_shared<ConstScore>() };
  Board board{ dimensions };
  std::list<std::shared_ptr<SearchNodeIface>> cgenerated{};
  std::size_t sum{ 0 };

  SUBCASE("gen depth 1 children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    auto collect_child = [&cgenerated, &sum] (auto child) {
      cgenerated.push_back(child);
      sum += std::dynamic_pointer_cast<SNBMock>(child)->get_marked_line().value();
    };
    parent->gen_children(collect_child);
    CHECK_EQ(cgenerated.size(), 24);
    CHECK_EQ(sum, 276);
    for (const auto& child : cgenerated) {
      CHECK_UNARY(child->has_parent());
      CHECK_EQ(child->get_depth(), 1);
      CHECK_EQ(child->get_player_to_act(), Player::COMPUTER);
    }
  }

  SUBCASE("gen depth 1, 2, and 3 children") {
    auto parent{ std::make_shared<SNBMock>(board, Player::ONE, scorer) };
    std::list<std::shared_ptr<SearchNodeIface>> depth_1_children{};
    std::list<std::shared_ptr<SearchNodeIface>> depth_2_children{};
    std::list<std::shared_ptr<SearchNodeIface>> depth_3_children{};
    auto collect_depth_1_child = [&depth_1_children] (auto child) { depth_1_children.push_back(child); };
    auto collect_depth_2_child = [&depth_2_children] (auto child) { depth_2_children.push_back(child); };
    auto collect_depth_3_child = [&depth_3_children] (auto child) { depth_3_children.push_back(child); };
    parent->gen_children(collect_depth_1_child);
    depth_1_children.front()->gen_children(collect_depth_2_child);
    depth_2_children.front()->gen_children(collect_depth_3_child);
    CHECK_EQ(depth_3_children.size(), 22);
    CHECK_EQ(depth_3_children.front()->get_depth(), 3);
    CHECK_EQ(depth_3_children.front()->get_player_to_act(), Player::COMPUTER);
  }

}

