#include "static.h"

int makefile(FILE *room_file){
  if (!(room_file = fopen(FILE_NAME, "r"))){
    room_file = fopen(FILE_NAME, "w");
    if (room_file == NULL) {
      fclose(room_file);
      return -1;
    }
    fclose(room_file);
    return 1;
  }
  fclose(room_file);
  return 0;
}

int readfile(){
  return 0;
}
