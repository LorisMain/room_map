#include "config.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int makefile(const char *file_name){
  FILE *room_file;
  if (!(room_file = fopen(file_name, "r"))){
    room_file = fopen(file_name, "w");
    if (room_file == NULL) {
      fclose(room_file);
      return -1;
    }
    fprintf(room_file, STARTER_TEMPLATE);
    fclose(room_file);
    return 1;
  }
  fclose(room_file);
  return 0;
}

int writefile(FILE *room_file, struct box* master_box){

  all_box_to_file(master_box, room_file);
  fprintf(room_file, ";");

  return 0;
}

int readfile(FILE *room_file, box* master_box){

  char line[LINE_SIZE];
  get_new_line(line, room_file);
  master_switch(line[0], line, room_file, NULL);
  return 0;
}

void obj_to_file(obj *to_put, FILE *file_p){
  char to_write[LINE_SIZE] = "";
  to_write[0] = '>';
  if (sizeof(to_put->name)/sizeof(char) > LINE_SIZE - 8) {
    return;
  }
  strncpy(&to_write[1], to_put->name, LINE_SIZE - 8);
  {
    int i = 0;
    for(i = 0; i < LINE_SIZE - 8 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
  }
  fprintf(file_p, "%s\n", to_write);
  memset(to_write, 0, sizeof(to_write)/sizeof(char));
  fprintf(file_p, ":%s", to_put->description);
  fprintf(file_p, "<%f<%f<%f\n", to_put->location[0], to_put->location[1], to_put->location[2]);
}

void box_to_file(box *to_put, FILE *file_p){
  char to_write[LINE_SIZE] = "";
  to_write[0] = '#';
  if (sizeof(to_put->name)/sizeof(char) > LINE_SIZE - 8) {
    return;
  }
  strncpy(&to_write[1], to_put->name, LINE_SIZE - 8);
  {
    int i = 0;
    for(i = 0; i < LINE_SIZE - 8 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
    to_write[i + 1] = to_put->box_format;
  }
  fprintf(file_p, "%s\n", to_write);
  memset(to_write, 0, sizeof(to_write)/sizeof(char));

  fprintf(file_p, ":%s", to_put->description);

  fprintf(file_p, "<%f<%f<%f\n", to_put->location[0], to_put->location[1], to_put->location[2]);

  if (to_put->box_format == '+') {
    fprintf(file_p, "++%f\n", to_put->height);
  }
  for (int i = 0; i < 128 && to_put->corners[i][0] != 0; i++) {
    fprintf(file_p, "%c%f%c%f%c%f\n", to_put->box_format, to_put->corners[i][0], to_put->box_format, to_put->corners[i][1], to_put->box_format, to_put->corners[i][2]);
  }
}

void all_box_to_file(box *to_put, FILE *file_p){
  box_to_file(to_put, file_p);
  struct obj *temp_o = to_put->first;
  while (temp_o != NULL) {
    obj_to_file(temp_o, file_p);
    temp_o = temp_o->next;
  }
  box *temp = to_put->inner;
  if (temp != NULL) {
    fprintf(file_p, "{\n");
    all_box_to_file(temp, file_p);
    fprintf(file_p, "}\n");
  }
  box *temp_b = to_put->next;
  if (temp_b != NULL) {
    all_box_to_file(temp_b, file_p);
  }
}
void print_box(struct box* to_print){
  for(int i = 0; i < LINE_SIZE/2; i++)
    printf("_");
  printf("\nBox(%c) name: %s\n", to_print->box_format, to_print->name);
  printf("Description: %s", to_print->description);
  if(to_print->box_format == '+')
    printf("\n%f", to_print->height);
  printf("\nLocation: %f, %f, %f\n\n", to_print->location[0], to_print->location[1], to_print->location[2]);
  printf("Corners:\n");
  for (int i = 0; i < 128 && to_print->corners[i][0] != '\0'; i++) {
    for (int j = 0; j < 3 && to_print->corners[i][j] != '\0'; j++){
      printf("%f", to_print->corners[i][j]);
      if (j != 2)
        printf(", ");
    }
    printf("\n");
  }
}

void print_obj(struct obj* to_print){
  for(int i = 0; i < LINE_SIZE/2; i++)
    printf("_");
  printf("\nObject name: %s\n", to_print->name);
  printf("Description: %s\n", to_print->description);
  printf("Location:\n%f, %f, %f\n", to_print->location[0], to_print->location[1], to_print->location[2]);
}

void print_all_b(box *start){
  printf(RED);
  for(int i = 0; i < LINE_SIZE/2; i++)
    printf("_");
  printf("\n" RESET);
  if (start == NULL) {
    return;
  }
  print_stats_b(start);
  obj *temp_o = start->first;
  while (temp_o != NULL) {
    printf(RED);
    for(int i = 0; i < LINE_SIZE/2; i++)
      printf("_");
    printf("\n" RESET);
    print_stats_o(temp_o);
    temp_o = temp_o->next;
  }
  box *temp = start->inner;
  if (temp != NULL) {
    print_all_b(temp);
  }
  box *temp_b = start->next;
  if (temp_b != NULL) {
    print_all_b(temp_b);
  }
}

int master_switch(char switcher, char *line, FILE *room_file, struct box *current_b){
  char dimention[128];
  
  switch(switcher){

    case '1':

      {
      int i;
      for(i = 1; i < LINE_SIZE && line[i] != SEPERATOR; i++)
        current_b->name[i - 1] = line[i];
      current_b->box_format = line[i + 1];
      }


      get_new_line(line, room_file);
      get_description(line, room_file, current_b->description);

      {
      char dimention_m[128] = { 0 };
      get_new_line(line, room_file);
      insert_corners(line, room_file, (float*)current_b->location, '<', dimention_m, 1);
      }

      master_switch(line[0], line, room_file, current_b);

      break;

    case '+':
      if (line[1] == '+') {
        for(int j = 2; j < sizeof(line) - 2; j++)
          dimention[j - 2] = line[j];
        sscanf(dimention, "%f", &current_b->height);
        get_new_line(line, room_file);
      }
      if(insert_corners(line, room_file, *current_b->corners, '+', dimention, -1) < 0)
        return -5;
      master_switch(line[0], line, room_file, current_b);
      break;

    case '-':
      if(insert_corners(line, room_file, *current_b->corners, '-', dimention, -1) < 0)
        return -5;
      master_switch(line[0], line, room_file, current_b);
      break;

    case '/':
      if(insert_corners(line, room_file, *current_b->corners, '/', dimention, 1) < 0)
        return -5;
      master_switch(line[0], line, room_file, current_b);
      break;

    case '#':
      current_b = append_new_box(current_b);

      {
      int i;
      for(i = 1; i < LINE_SIZE && line[i] != SEPERATOR; i++)
        current_b->name[i - 1] = line[i];

      current_b->box_format = line[i + 1];
      }


      get_new_line(line, room_file);
      get_description(line, room_file, current_b->description);

      {
      char dimention_m[128] = { 0 };
      get_new_line(line, room_file);
      insert_corners(line, room_file, (float*)current_b->location, '<', dimention_m, 1);
      }

      master_switch(line[0], line, room_file, current_b);
      break;

    case '>':
      {
      obj *current_o = put_object_in_box(current_b);

      {
      int i;
      for(i = 1; i < LINE_SIZE && line[i] != SEPERATOR; i++)
        current_o->name[i - 1] = line[i];
      }

      get_new_line(line, room_file);
      get_description(line, room_file, current_o->description);

      {
      char dimention_o[128] = { 0 };
      get_new_line(line, room_file);
      insert_corners(line, room_file, (float*)current_o->location, '<', dimention_o, 1);
      }
      }
      master_switch(line[0], line, room_file, current_b);

      break;

    case '{':
      get_new_line(line, room_file);
      master_switch('1', line, room_file, go_level_down_box(current_b));

      break;
    case '}':
      get_new_line(line, room_file);
      master_switch(line[0], line, room_file, go_level_up_box(current_b));
      break;

    case ';':
      return 0;
      break;

    default:
      return -6;
      break;
  }
  return 0;
}

int get_description(char *line, FILE *room_file, char *description){
  if (line[0] == ':') {
    int i;
    for (i = 0; i < LINE_SIZE - 2 && line[i] != '\0'; i++) {
      description[i] = line[i + 1];
    }
    if (description[i] == '\n') {
      description[i] = '\0';
      return 0;
    }
    description[i + 1] = '\0';
    return 0;
  }
  return -1;
}

int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN, char seperator){
  for (*len1 = 1; line[*len1] != seperator && *len1 < LINE_SIZE; *len1+=1);
  for (*len2 = *len1 + 1; line[*len2] != seperator && *len2 < (LINE_SIZE - *len1); *len2+=1);

  if(*len2 - *len1 > MAX_LEN + 1)
    return -1;
  return 0;
}

int get_new_line(char *line, FILE *room_file){
  memset(line, 0, LINE_SIZE);
  fgets(line, LINE_SIZE, room_file);
  return 0;
}

int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size){

  if (max_size < 0)
    max_size = -1 * (max_size * LINE_SIZE);

  for(int i = 0; line[0] == format; i++){

    if(i > max_size - 1)
      return -1;

    int t_len[2];
    get_sep_spacing(&t_len[0], &t_len[1], line, -1, format);


    memset(dimention, 0, 128);
    for(int j = 1; j < t_len[0]; j++)
      dimention[j - 1] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i));
    memset(dimention, 0, 128);

    for(int j = t_len[0] + 1; j < t_len[1]; j++)
      dimention[j - (1 + t_len[0])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i + 1 ));
    memset(dimention, 0, 128);

    for(int j = t_len[1] + 1; j < LINE_SIZE - 1; j++)
      dimention[j - (1 + t_len[1])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i + 2));
    memset(dimention, 0, 128);

    get_new_line(line, room_file);

    if(line[1] == format)
      return 1;

  }
  return 0;
}
