#include "static.h"
#include <cstdio>

FILE *room_file;

int main(){

  readfile(room_file);
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
