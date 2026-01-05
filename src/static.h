#include <stdio.h>

#define FILE_NAME "room_file.txt"

int makefile(FILE *room_file);
int readfile();

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
