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

#include <dpp/appcommand.h>
#include <rps/commands/leave.h>

dpp::slashcommand leave_command::register_command(dpp::cluster &bot) {
  return dpp::slashcommand("leave", "Leave the RPS queue", bot.me.id)
      .set_dm_permission(true);
}

void leave_command::route(const dpp::slashcommand_t &event) {
  dpp::cluster *bot = event.from->creator;
  event.reply("yo its leave");
}