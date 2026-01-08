#include "config.h"

FILE *room_file;

int main(){

  if(makefile(room_file) < 0){
    printf("Error ensuring file exists!\n");
  }
  room_file = fopen(FILE_NAME, "w");
  fprintf(room_file, "hallo");
  fclose(room_file);
  
  return 0;
}

