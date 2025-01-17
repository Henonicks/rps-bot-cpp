/************************************************************************************
 *
 * Copyright 2024 tarolling
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/

#pragma once

#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/snowflake.h>
#include <dpp/timer.h>
#include <dpp/user.h>
#include <memory>
#include <utility>

namespace game {
struct player_info {
  dpp::user player;
  dpp::slashcommand_t init_interaction;
  std::string choice;
  unsigned int score{0};
  dpp::timer game_timer{};

  player_info(const dpp::user &p, dpp::slashcommand_t i)
      : player(p), init_interaction(std::move(i)) {}
};

struct rps_lobby {
  unsigned int id{0};
  unsigned int game_number{1};
  std::vector<std::shared_ptr<player_info>> players;
};

/**
 * @brief Initialize global game state
 *
 * @param bot creating D++ cluster
 */
void init(dpp::cluster &bot);

/**
 * @brief Finds a lobby that the player is in, if it exists
 *
 * @param user
 * @return unsigned int lobby id
 */
unsigned int find_player_lobby_id(const dpp::snowflake player_id);

/**
 * @brief Finds an open lobby avilable to join
 *
 * @return unsigned int lobby id
 */
unsigned int find_open_lobby_id();

unsigned int get_global_lobby_id();
void increment_global_lobby_id();
void decrement_global_lobby_id();
void remove_lobby_from_queue(const unsigned int lobby_id, const bool game_over);
unsigned int create_lobby();
void add_player_to_lobby(const unsigned int lobby_id,
                         const dpp::slashcommand_t &event);
void remove_player_from_lobby(const unsigned int lobby_id,
                              const dpp::snowflake player_id);
void set_player_choice(const dpp::snowflake player_id,
                       const std::string &choice);
std::string get_player_choice(const dpp::snowflake player_id);
unsigned int get_num_players(const unsigned int lobby_id);
rps_lobby get_lobby(const unsigned int lobby_id);
unsigned int get_player_score(const unsigned int lobby_id,
                              const dpp::snowflake player_id);
std::shared_ptr<player_info> get_player_info(const dpp::snowflake player_id);
void reset_choices(const unsigned int lobby_id);
void increment_player_score(const unsigned int lobby_id,
                            const unsigned int player_num);
unsigned int get_game_num(const unsigned int lobby_id);
void increment_game_num(const unsigned int lobby_id);
bool check_both_responses(const unsigned int lobby_id);
std::string determine_winner(const unsigned int lobby_id);
std::string calculate_winner(const std::string &player_one_choice,
                             const std::string &player_two_choice);
void send_game_messages(const unsigned int lobby_id);
bool is_game_complete(const unsigned int lobby_id);
void send_result_messages(const unsigned int lobby_id,
                          const unsigned int winner, const unsigned int loser);
void handle_game(const dpp::button_click_t &event);
} // namespace game
