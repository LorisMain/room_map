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
int get_first_line(char *line, char *name, FILE *room_file, char STARTER);
int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN);
int get_number(int *len1, int *len2, char *line);
int get_new_line(char *line, FILE *room_file);
int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size);

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
