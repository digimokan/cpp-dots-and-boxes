/*******************************************************************************
module:   SearchNodeIface
author:   digimokan
date:     11 FEB 2019
purpose:  a dots and boxes search node
*******************************************************************************/

#ifndef SEARCH_NODE_IFACE_HPP
#define SEARCH_NODE_IFACE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <functional>
#include <memory>

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class Board;
enum class Player;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class SearchNodeIface {

public:

  // destructor
  virtual ~SearchNodeIface () = default;

  // operators
  SearchNodeIface (const SearchNodeIface& in) = default;
  SearchNodeIface& operator= (const SearchNodeIface& rh) = default;
  SearchNodeIface (SearchNodeIface&& in) = default;
  SearchNodeIface& operator= (SearchNodeIface&& rh) = default;

  // base / derived methods
  virtual bool is_terminal () const = 0;
  virtual int64_t calc_score () const = 0;
  virtual int64_t calc_player_score (Player player) const = 0;
  virtual void set_minimax_score () = 0;
  virtual int64_t get_minimax_score () = 0;
  virtual bool has_parent () const = 0;
  virtual bool has_children () const = 0;
  virtual std::size_t get_depth () const = 0;
  virtual void set_depth (std::size_t in_depth) = 0;
  virtual Player get_player_to_act () const = 0;
  virtual Board get_board () const = 0;
  virtual std::optional<std::size_t> get_marked_line () const = 0;
  virtual void gen_children (std::function<void(std::shared_ptr<SearchNodeIface>)> act_on_child) = 0;
  virtual std::shared_ptr<SearchNodeIface> gen_new_root (std::size_t line_num) = 0;
  virtual void set_minimax_score_from_children () = 0;
  virtual std::shared_ptr<SearchNodeIface> get_minimax_child () = 0;
  virtual void set_alpha_or_beta (std::size_t minimax_score) = 0;

protected:

  // constructors
  SearchNodeIface () = default;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // SEARCH_NODE_IFACE_HPP

