#include <cstdio>
#include <stdio.h>

#define NAME_SIZE 64
#define MAX_SEARCH 128
#define DESCRIBE_SIZE 127

#define ROOM_STARTER '@'
#define BOX_STARTER '#'
#define OBJECT_STARTER '>'
#define SEPERATOR '_'

#define FILE_NAME "room_file.txt"
#define TEST_FILE "test_file.txt"

int makefile(const char *room_file);
//int readfile(FILE *room_file, struct room, struct box, struct object);
int readfile(FILE *room_file, struct room *room_p);
int writefile(FILE *room_file, struct room *room_p);

int get_first_line(char *line, char *name, FILE *room_file, char STARTER);
int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN, char seperator);
int get_number(int *len1, int *len2, char *line);
int get_new_line(char *line, FILE *room_file);
int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size);
int master_switch(char switcher, char *line, FILE *room_file, struct room *current_r, struct box *current_b, int operation_to_do);
int get_description(char *line, FILE *room_file, char *description);
room *append_new_room(struct room *first);
box *append_new_box(struct box *first);
box *go_level_down_box(struct box *current);
box *append_box_to_room(struct room *current);
struct obj *put_object_next_to_box(struct box *current);
obj *put_object_in_box(struct box *current);
box *go_level_up_box(struct box *current);
void print_all(room *first);
void room_to_file(struct room* to_put, FILE *file_p);
void obj_to_file(obj *to_put, FILE *file_p);
void box_to_file(box *to_put, FILE *file_p);
void all_box_to_file(box *to_put, FILE *file_p);

struct room{
  char name[64] = "";
  float corners[128][3] = { { 0 } };
  float size[3] = { 0 };
  float height = 0;
  int room_number = 1;
  char room_format = '+';
  struct box* first = NULL;
  struct room* next = NULL;
  //struct object* content = NULL;
};
struct box{
  char name[64] = "";
  char description[256] = "";
  float corners[128][3] = { { 0 } };
  float height = 0;
  float location[3] = { 0 };
  int box_number = 1;
  char box_format = '+';
  struct obj* first = NULL;
  struct box* inner = NULL;
  struct box* next = NULL;
  struct box* prev = NULL;
};
struct obj{
  char name[64] = "";
  char description[256] = "";
  int object_number = 1;
  float location[3] = { 0 };
  struct obj* next = NULL;
  struct box* prev = NULL;
};
