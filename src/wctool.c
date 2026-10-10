/*
 * Copyright (C) 2026 TheCRatTime
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int main(int argc, char** argv) {
  char buffer[4096];
  size_t bytes = 0;
  size_t lines = 0;
  size_t words = 0;
  int readed = 0;
  FILE* file = NULL;
  int in_word = 0;
  
  if (argc < 2) {
    printf("Usage: %s FILE\n", argv[0]);
    return 1;
  }

  file = fopen(argv[1], "rb");
  if (file == NULL) {
    perror(argv[0]);
    return 1;
  }
  
  fseek(file, 0, SEEK_END);
  bytes = ftell(file);
  fseek(file, 0, SEEK_SET);

  readed = fread(buffer, 1, 4095, file);
  while(readed > 0) {
    buffer[readed] = '\0';
    for(int i = 0; i < readed+1; i++) {
      if (buffer[i] == '\n') {
        lines++;
      }
      
      if (isspace(buffer[i])) {
        in_word = 0;
      } else if (!in_word) {
        in_word++;
        words++;
      }
    }

    readed = fread(buffer, 1, 4095, file);
  }

  if (words != 0) {
    words--;
  }

  fclose(file);
  
  printf(
         "wctool:\n"
         "bytes: %lu\n"
         "words: %lu\n"
         "lines: %lu\n",
         bytes, words, lines);
  return 0;
}
