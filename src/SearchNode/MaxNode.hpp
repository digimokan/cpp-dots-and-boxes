/*******************************************************************************
module:   MaxNode
author:   digimokan
date:     12 FEB 2019
purpose:  a MAX node impl of SearchNodeBase
          --> has MIN node children
          --> seeks to find the MAX of its children nodes
*******************************************************************************/

#ifndef MAX_NODE_HPP
#define MAX_NODE_HPP 1

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "SearchNodeBase.hpp"

/*******************************************************************************
* FORWARD DECLARES
*******************************************************************************/

class MinNode;

/*******************************************************************************
* INTERFACE
*******************************************************************************/

class MaxNode : public SearchNodeBase, public std::enable_shared_from_this<MaxNode> {

public:

  // constructors
  MaxNode () = delete;
  MaxNode (Board board, Player player_to_act, std::shared_ptr<ScoreIface> score_iface);
  explicit MaxNode (const std::shared_ptr<MinNode>& parent);

  // destructor
  ~MaxNode () override = default;

  // operators
  MaxNode (const MaxNode& in) = default;
  MaxNode& operator= (const MaxNode& rh) = default;
  MaxNode (MaxNode&& in) = default;
  MaxNode& operator= (MaxNode&& rh) = default;

  // base / derived methods
  std::shared_ptr<SearchNodeIface> get_minimax_child () final;

private:

  // base / derived methods
  std::shared_ptr<SearchNodeBase> create_detached_child () final;

};

/*******************************************************************************
* END
*******************************************************************************/

#endif // MAX_NODE_HPP

