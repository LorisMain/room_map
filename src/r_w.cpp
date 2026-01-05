#include <stdio.h>
#define FILE_NAME "room_file.txt"

struct room{
  char name[64];
  float corners[64];
  float height;
  struct box* first;
  struct room* next;
  struct object* content;
};
struct box{
  char name[64];
  float corners[128];
  float size[3];
  float height;
  float location[3];
  struct object* first;
  struct box* next;
  struct box* inner;
};
struct object{
  char name[64];
  float corners[128];
  float size[3];
  float location[3];
  struct object* next;
};

FILE *room_file;

int makefile();
int readfile();

int main(){

  if(makefile() < 0){
    printf("Error ensuring file exists!\n");
  }
  room_file = fopen(FILE_NAME, "w");
  fprintf(room_file, "hallo");
  fclose(room_file);
  
  return 0;
}

int makefile(){
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
