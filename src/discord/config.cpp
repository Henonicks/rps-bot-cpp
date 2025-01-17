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
#include <dpp/dpp.h>
#include <dpp/json.h>
#include <fstream>
#include <rps/rps.h>

namespace config {

static json configdocument;

void init(const std::string &config_file) {
  /* Set up the bot cluster and read the configuration json */
  std::ifstream configfile(config_file);
  configfile >> configdocument;
}

bool exists(const std::string &key) { return configdocument.contains(key); }

json &get(const std::string &key) {
  if (key.empty()) {
    return configdocument;
  }
  return configdocument.at(key);
}
}; // namespace config