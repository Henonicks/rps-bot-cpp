/************************************************************************************
 *
 * Copyright 1993,2001,2023 Craig Edwards <brain@ssod.org>
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
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dpp/dpp.h>
#include <rps/commandline.h>
#include <rps/config.h>
#include <rps/game.h>
#include <rps/listeners.h>
#include <rps/logger.h>

int main(int argc, char const *argv[]) {
  (void)std::setlocale(LC_ALL, "en_US.UTF-8");

  config::init("config.json");
  logger::init(config::get("log"));
  commandline_config cli = commandline::parse(argc, argv);

  dpp::cluster bot(config::get("token"), dpp::i_guilds, config::get("shards"),
                   cli.cluster_id, cli.max_clusters, true,
                   dpp::cache_policy::cpol_none);

  // i18n::load_lang(bot);

  if (cli.display_commands) {
    std::cerr << listeners::json_commands(bot) << "\n";
    exit(0);
  }

  bot.set_websocket_protocol(dpp::ws_etf);

  // security::init(bot);

  bot.on_log(&logger::log);
  bot.on_slashcommand(&listeners::on_slashcommand);
  bot.on_button_click(&listeners::on_buttonclick);
  // bot.on_select_click(&game_select);
  // bot.on_form_submit(&game_input);
  bot.on_ready(&listeners::on_ready);

  /* Initialize game state */
  game::init(bot);

  /* Start bot */
  bot.start(dpp::st_wait != 0U);
}
