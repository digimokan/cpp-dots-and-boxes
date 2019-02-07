/*******************************************************************************
module:   BoxMarks
author:   digimokan
date:     04 FEB 2019
purpose:  map of box_num -> marking_player
*******************************************************************************/

/*******************************************************************************
* SYSTEM INCLUDES
*******************************************************************************/

#include <cassert>
#include <cmath>
#include <cstddef>
#include <numeric>
#include <unordered_map>

/*******************************************************************************
* USER INCLUDES
*******************************************************************************/

#include "BoxMarks.hpp"
#include "Player.hpp"

/*******************************************************************************
* CONSTRUCTORS
*******************************************************************************/

BoxMarks::BoxMarks (std::size_t board_dimensions) {
  this->init_unmarked_boxnums(board_dimensions);
  this->init_player_boxmarks();
}

/*******************************************************************************
* SPECIALIZED METHODS
*******************************************************************************/

std::size_t BoxMarks::get_num_boxes () const {
  return (this->get_num_unmarked() + this->get_num_marked());
}

std::size_t BoxMarks::get_board_dimensions () const {
  return static_cast<std::size_t>( std::sqrt(this->get_num_boxes()) );
}

bool BoxMarks::is_marked (std::size_t box_num) const {
  return (this->marks.count(box_num) != 0);
}

bool BoxMarks::not_marked (std::size_t box_num) const {
  return (! this->is_marked(box_num));
}

void BoxMarks::mark (std::size_t box_num, Player player) {
  assert(! this->unmarked_boxnums.empty());
  assert(this->marks.count(box_num) == 0);
  assert(this->unmarked_boxnums.count(box_num) == 1);
  assert(this->marked_boxnums.count(box_num) == 0);
  assert(player_boxmarks.at(player).count(box_num) == 0);
  this->marks.emplace(std::make_pair(box_num, player));
  this->unmarked_boxnums.erase(box_num);
  this->marked_boxnums.emplace(box_num);
  this->player_boxmarks.at(player).emplace(box_num);
}

std::size_t BoxMarks::get_num_unmarked () const {
  return this->unmarked_boxnums.size();
}

std::size_t BoxMarks::get_num_marked () const {
  return this->marked_boxnums.size();
}

bool BoxMarks::all_marked () const {
  return this->unmarked_boxnums.empty();
}

void BoxMarks::for_each_player_boxmark (Player player,
    const std::function<void(std::size_t box_num)>& act_on_box_num) const {
  for (const auto& box_num : this->player_boxmarks.at(player))
    act_on_box_num(box_num);
}

/*******************************************************************************
* HELPER METHODS
*******************************************************************************/

void BoxMarks::init_unmarked_boxnums (std::size_t board_dimensions) {
  for (std::size_t i = 0; i < (board_dimensions * board_dimensions); ++i)
    this->unmarked_boxnums.emplace(i);
}

void BoxMarks::init_player_boxmarks () {
  for (const auto& player : PlayerVals) {
    std::set<size_t> empty_set{};
    this->player_boxmarks.emplace(player, empty_set);
  }
}

