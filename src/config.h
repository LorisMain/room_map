#include <cstdio>
#include <stdio.h>

#define NAME_SIZE 64
#define MAX_SEARCH 128

#define ROOM_STARTER '@'
#define SEPERATOR '_'

#define FILE_NAME "room_file.txt"

int makefile(FILE *room_file);
//int readfile(FILE *room_file, struct room, struct box, struct object);
int readfile(FILE *room_file);

struct room{
  char name[64] = "";
  float corners[128] = { 0 };
  float size[3] = { 0 };
  float height = 0;
  int room_number = 1;
  char room_format = '+';
  struct box* first = NULL;
  struct room* next = NULL;
  struct object* content = NULL;
};
struct box{
  char name[64];
  float corners[128];
  float size[3];
  float height;
  float location[3];
  int box_number;
  char room_format;
  struct object* first;
  struct box* inner;
  struct box* next;
};
struct object{
  char name[64];
  float corners[128];
  float height;
  float size[3];
  float location[3];
  int object_number;
  char room_format;
  struct object* next;
};
