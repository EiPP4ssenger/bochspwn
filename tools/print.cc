/////////////////////////////////////////////////////////////////////////
//
// Authors: Mateusz Jurczyk (mjurczyk@google.com)
//          Gynvael Coldwind (gynvael@google.com)
//
// Copyright 2013-2018 Google LLC
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <stdint.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "common.h"
#include "logging.pb.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <input file> <modules list>\n", argv[0]);
    return EXIT_FAILURE;
  }

  std::vector<module_info> modules;
  if (!LoadModuleList(argv[2], &modules)) {
    fprintf(stderr, "Unable to load the module list from \"%s\".\n", argv[2]);
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1], "rb");
  if (!f) {
    fprintf(stderr, "Unable to open input file \"%s\".\n", argv[1]);
    return EXIT_FAILURE;
  }

  log_data_st ld;
  while (LoadNextRecord(f, NULL, &ld)) {
    printf("%s", LogDataAsText(ld, modules).c_str());
  }

  if (!feof(f)) {
    fprintf(stderr, "Failure at offset %lu\n", ftell(f));
  }

  fclose(f);
  return EXIT_SUCCESS;
}
