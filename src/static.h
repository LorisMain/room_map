#include <cstdio>
#include <stdio.h>

#define NAME_SIZE 64

#define ROOM_STARTER '@'
#define SEPERATOR '_'

#define FILE_NAME "room_file.txt"

int makefile(FILE *room_file);
//int readfile(FILE *room_file, struct room, struct box, struct object);
int readfile(FILE *room_file);
int get_first_line(char *line, char *name, FILE *room_file, char STARTER);
int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN);
int get_number(int *len1, int *len2, char *line);
int get_new_line(char *line, FILE *room_file);
int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size);

struct room{
  char name[64];
  float corners[128];
  float size[3];
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
  struct box* inner;
  struct box* next;
};
struct object{
  char name[64];
  float corners[128];
  float height;
  float size[3];
  float location[3];
  struct object* next;
};
