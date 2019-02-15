/*******************************************************************************
module:   SearchNodeBase
author:   digimokan
date:     11 FEB 2019
purpose:  a base class impl of SearchNode
*******************************************************************************/

#ifndef SEARCH_NODE_BASE_HPP
#define SEARCH_NODE_BASE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstddef>
#include <cstdint>
#include <list>
#include <memory>
#include <optional>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "Board.hpp"
#include "Player.hpp"
#include "SearchNodeIface.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class ScoreIface;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class SearchNodeBase : public SearchNodeIface {

public:

  // constructors
  SearchNodeBase () = delete;

  // destructor
  ~SearchNodeBase () override = default;

  // operators
  SearchNodeBase (const SearchNodeBase& in) = default;
  SearchNodeBase& operator= (const SearchNodeBase& rh) = default;
  SearchNodeBase (SearchNodeBase&& in) = default;
  SearchNodeBase& operator= (SearchNodeBase&& rh) = default;

  // base / derived methods
  bool is_terminal () const final;
  int64_t calc_score () const final;
  int64_t calc_player_score (Player player) const final;
  void set_minimax_score () final;
  int64_t get_minimax_score () final;
  bool has_parent () const final;
  std::shared_ptr<SearchNodeIface> get_parent () const final;
  bool has_children () const final;
  std::size_t get_depth () const final;
  void set_depth (std::size_t in_depth) final;
  Player get_player_to_act () const final;
  Board get_board () const final;
  std::shared_ptr<ScoreIface> get_scorer () const final;
  std::optional<std::size_t> get_marked_line () const final;
  void add_child (const std::shared_ptr<SearchNodeIface>& child) final;
  void gen_children (std::function<void(std::shared_ptr<SearchNodeIface>)> act_on_child) final;
  bool cutoff_gen_children () const override { return false; }
  std::shared_ptr<SearchNodeIface> gen_new_root (std::size_t line_num) final;
  void set_minimax_score_from_children () final;
  std::shared_ptr<SearchNodeIface> get_minimax_child () override = 0;
  void set_alpha_or_beta (int64_t minimax_score) override { }
  std::optional<int64_t> get_alpha_or_beta () const override { return std::nullopt; }

protected:

  // constructors
  SearchNodeBase (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface);
  explicit SearchNodeBase (const std::shared_ptr<SearchNodeBase>& parent);

  // base / derived methods
  virtual std::shared_ptr<SearchNodeBase> create_detached_child () = 0;

  // specialized methods
  void mark_line (Player player, std::size_t line_num);
  std::shared_ptr<SearchNodeIface> get_max_child () const;
  std::shared_ptr<SearchNodeIface> get_min_child () const;

  // fields
  Board board;
  Player player_to_act;
  std::shared_ptr<ScoreIface> scorer;
  std::weak_ptr<SearchNodeBase> parent;
  std::list<std::shared_ptr<SearchNodeIface>> children;

private:

  // fields
  std::optional<std::size_t> marked_line;
  std::size_t depth;
  std::optional<int64_t> minimax_score;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SEARCH_NODE_BASE_HPP

