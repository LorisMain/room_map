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
  /*
  struct room *temp = NULL;
  temp = append_new_room(NULL);
  (*temp).room_number = 4;
  printf("%d", (*temp).room_number);
  (*append_new_room(temp)).room_number = 2;
  printf("%d", (*temp->next).room_number);
  */
  /*
  int len1;
  int len2;
  char line[128];
  int *temp = &len1;
  int *temp2 = &len2;
  
  for (*temp = 0; line[*temp] != SEPERATOR && *temp < 128; *temp+=1);
  printf("%d", *temp);
  */
  //get_sep_spacing(&len1, &len2, line, 4);

  return 0;
}
