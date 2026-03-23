#include <cstdio>
#include <stdio.h>

#define LINE_SIZE 127

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define BOX_STARTER '#'
#define OBJECT_STARTER '>'
#define SEPERATOR '_'

#define HELP_TEXT "Commands:\n-d: (delete) {>d_[box/object_name]} will delete current room\n-f: (file) open file that is specefied after\n-h: (help) prints this text\n-l: (list){>lx} will list just names, if x == a it will list atributes of box/object given after \"_\", if x == s it will list all boxes and objects under current one\n-m: (move){>mx_[box_name]} will move current position to the specefied box, if x == b it will move back\n-n: (new){nx} will create new box, or object if x == o, inside current box\n-s: (search){s_[text]} will search thrugh all the boxes underneath and return boxes and objects with [text] in the beginning of their name\n"
#define STARTER_TEMPLATE "#master_/\n:master\n<0.0<0.0<0.0\n/0/0/0\n;"

struct box{
  char name[64] = "";
  char description[127] = "";
  float corners[128][3] = { { 0 } };
  float height = 0;
  float location[3] = { 0 };
  char box_format = '+';
  struct obj* first = NULL;
  struct box* inner = NULL;
  struct box* next = NULL;
  struct box* prev = NULL;
};
struct obj{
  char name[64] = "";
  char description[127] = "";
  float location[3] = { 0 };
  struct obj* next = NULL;
  struct box* prev = NULL;
};

//essential functions
int action_switch(char *in, box** current, box **master_box, char *line);


//r_w functions
int get_first_line(char *line, char *name, FILE *room_file, char STARTER);
int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN, char seperator);
int get_number(int *len1, int *len2, char *line);
int get_new_line(char *line, FILE *room_file);
int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size);
int master_switch(char switcher, char *line, FILE *room_file, struct box *current_b);
int get_description(char *line, FILE *room_file, char *description);

//linked functions
box *append_new_box(struct box *first);
box *go_level_down_box(struct box *current);
box *go_level_up_box(struct box *current);
obj *put_object_in_box(struct box *current);

//file functions
int makefile(const char *room_file);
int readfile(FILE *room_file, struct box *master_box);
int writefile(FILE *room_file, struct box *master_box);

void obj_to_file(obj *to_put, FILE *file_p);
void box_to_file(box *to_put, FILE *file_p);
void all_box_to_file(box *to_put, FILE *file_p);

//printing functions
void print_all_b(box* start);
void print_box(box* to_print);
void print_obj(obj* to_print);
void print_path_b(box *current);
void print_path_o(obj *current);
void print_stats_b(box* current);
void print_stats_o(obj* current);
void print_searched_under(char *in, box **current);
void print_atributes(box **current, char *in);
void print_names(box *current);

//creation and destruction functions
void new_object(box* current);
void new_box(box* current);
void delete_with_name(char *in, box* current);
