#pragma once

#include <ctime>
#include <dpp/snowflake.h>
#include <dpp/user.h>
#include <list>
#include <optional>
#include <sys/types.h>

struct rps_game {
  unsigned int id;
  std::vector<dpp::user> players;
};

class state_t {
  class RPSModule *creator;

public:
  time_t next_tick;
  bool terminating;
  unsigned int global_game_id;
  /* Beginning with a single, global queue */
  std::list<struct rps_game> games;
  state_t(const state_t &) = default;
  state_t();
  state_t(RPSModule *_creator);
  ~state_t();
  state_t(state_t &&other) noexcept = default;            // move constructor
  state_t &operator=(const state_t &other) = default;     // copy assignment
  state_t &operator=(state_t &&other) noexcept = default; // move assignment
  void tick();
  std::optional<rps_game> find_player_game(dpp::user &user);
  std::optional<std::reference_wrapper<rps_game>> find_open_game();
};