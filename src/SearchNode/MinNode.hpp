/*******************************************************************************
module:   MinNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MIN node impl of SearchNodeBase
          --> has MAX node children
          --> seeks to find the MIN of its children nodes
*******************************************************************************/

#ifndef MIN_NODE_HPP
#define MIN_NODE_HPP 1

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cstdint>
#include <optional>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "SearchNodeBase.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class MaxNode;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MinNode : public SearchNodeBase, public std::enable_shared_from_this<MinNode> {

public:

  // constructors
  MinNode () = delete;
  MinNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface);
  explicit MinNode (const std::shared_ptr<MaxNode>& parent);

  // destructor
  ~MinNode () override = default;

  // operators
  MinNode (const MinNode& in) = default;
  MinNode& operator= (const MinNode& rh) = default;
  MinNode (MinNode&& in) = default;
  MinNode& operator= (MinNode&& rh) = default;

  // base / derived methods
  bool cutoff_gen_children () const final;
  std::shared_ptr<SearchNodeIface> get_minimax_child () final;
  void set_alpha_or_beta (int64_t minimax_score) final;
  std::optional<int64_t> get_alpha_or_beta () const final;

private:

  // base / derived methods
  std::shared_ptr<SearchNodeBase> create_detached_child () final;

  // fields
  std::optional<int64_t> beta;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MIN_NODE_HPP

