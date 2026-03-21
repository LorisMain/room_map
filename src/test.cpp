#include "config.h"
#include <cstdio>

FILE *room_file;
FILE *test_file;
room *append_new_room(struct room *first);

int main(){

  room *room_p = append_new_room(NULL);
  
  room_file = fopen(FILE_NAME, "r");
  readfile(room_file, room_p);
  fclose(room_file);

  //makefile(TEST_FILE);
  test_file = fopen(TEST_FILE, "w");
  writefile(test_file, room_p);
  fclose(test_file);

  return 0;
}
