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
    fclose(room_file);
    return 1;
  }
  fclose(room_file);
  return 0;
}

int writefile(FILE *room_file, struct room *room_p){

  room_to_file(room_p, room_file);
  all_box_to_file(room_p->first, room_file);
  fprintf(room_file, ";");

  return 0;
}

int readfile(FILE *room_file, room *room_p){

  char line[MAX_SEARCH];
  get_new_line(line, room_file);
  master_switch('@', line, room_file, room_p, NULL, 0);
  //print_all(room_p);
  return 0;
}

void room_to_file(struct room* to_put, FILE *file_p){
  char to_write[MAX_SEARCH] = "";
  to_write[0] = '@';
  if (sizeof(to_put->name)/sizeof(char) > MAX_SEARCH - 8) {
    return;
  }
  strncpy(&to_write[1], to_put->name, MAX_SEARCH - 8);
  {
    int i = 0;
    for(i = 0; i < MAX_SEARCH - 8 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
    sprintf(&to_write[i + 1], "%d", to_put->room_number);
    for(i = 0; i < MAX_SEARCH - 2 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
    to_write[i + 1] = to_put->room_format;
  }
  fprintf(file_p, "%s\n", to_write);
  memset(to_write, 0, sizeof(to_write)/sizeof(char));
  if (to_put->room_format == '+') {
    fprintf(file_p, "++%f\n", to_put->height);
  }
  for (int i = 0; i < 128 && to_put->corners[i][0] != 0; i++) {
    fprintf(file_p, "%c%f%c%f%c%f\n", to_put->room_format, to_put->corners[i][0], to_put->room_format, to_put->corners[i][1], to_put->room_format, to_put->corners[i][2]);
  }
}

void obj_to_file(obj *to_put, FILE *file_p){
  char to_write[MAX_SEARCH] = "";
  to_write[0] = '>';
  if (sizeof(to_put->name)/sizeof(char) > MAX_SEARCH - 8) {
    return;
  }
  strncpy(&to_write[1], to_put->name, MAX_SEARCH - 8);
  {
    int i = 0;
    for(i = 0; i < MAX_SEARCH - 8 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
    sprintf(&to_write[i + 1], "%d", to_put->object_number);
    for(i = 0; i < MAX_SEARCH - 2 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
  }
  fprintf(file_p, "%s\n", to_write);
  memset(to_write, 0, sizeof(to_write)/sizeof(char));
  fprintf(file_p, ":%s", to_put->description);
  fprintf(file_p, "<%f<%f<%f\n", to_put->location[0], to_put->location[1], to_put->location[2]);
}

void box_to_file(box *to_put, FILE *file_p){
  char to_write[MAX_SEARCH] = "";
  to_write[0] = '#';
  if (sizeof(to_put->name)/sizeof(char) > MAX_SEARCH - 8) {
    return;
  }
  strncpy(&to_write[1], to_put->name, MAX_SEARCH - 8);
  {
    int i = 0;
    for(i = 0; i < MAX_SEARCH - 8 && to_write[i] != '\0'; i++);
    to_write[i] = SEPERATOR;
    sprintf(&to_write[i + 1], "%d", to_put->box_number);
    for(i = 0; i < MAX_SEARCH - 2 && to_write[i] != '\0'; i++);
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

void print_room(struct room* to_print){
  for(int i = 0; i < MAX_SEARCH/2; i++)
    printf("_");
  printf("\nRoom(%c) %d name: %s\n", to_print->room_format, to_print->room_number, to_print->name);
  if (to_print->room_format == '+') {
    printf("\nHeight: %f", to_print->height);
  }
  printf("\nCorners:\n");
  for (int i = 0; i < 128 && to_print->corners[i][0] != '\0'; i++) {
    for (int j = 0; j < 3 && to_print->corners[i][j] != '\0'; j++){
      printf("%f", to_print->corners[i][j]);
      if (j != 2)
        printf(", ");
    }
    printf("\n");
  }
}
void print_box(struct box* to_print){
  for(int i = 0; i < MAX_SEARCH/2; i++)
    printf("_");
  printf("\nBox(%c) %d name: %s\n", to_print->box_format, to_print->box_number, to_print->name);
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
  for(int i = 0; i < MAX_SEARCH/2; i++)
    printf("_");
  printf("\nObject %d name: %s\n", to_print->object_number, to_print->name);
  printf("Description: %s\n", to_print->description);
  printf("Location:\n%f, %f, %f\n", to_print->location[0], to_print->location[1], to_print->location[2]);
}

void print_all_b(box *start){
  print_box(start);
  box *temp = start->inner;
  while (temp != NULL) {
    print_all_b(temp);
  }
  box *temp_b = start->next;
  while (temp_b != NULL) {
    print_all_b(temp_b);
  }
  obj *temp_o = start->first;
  while (temp_o != NULL) {
    print_obj(temp_o);
  }
}

void print_all(struct room *first){
  print_room(first);
  print_all_b(first->first);
}
/*
  box *temp = first->first;
  while (temp != NULL) {
    print_box(temp);
    box *temp_b = temp->inner;
    obj *temp_oo = temp->first;
    while (temp_oo != NULL) {
      print_obj(temp_oo);
      temp_oo = temp_oo->next;
    }
    while (temp_b != NULL) {
      print_box(temp_b);
      obj *temp_o = temp_b->first;
      while (temp_o != NULL) {
        print_obj(temp_o);
        temp_o = temp_o->next;
      }
      temp_b = temp_b->next;
    }
    temp = temp->next;
  }
  */

int master_switch(char switcher, char *line, FILE *room_file, struct room *current_r, struct box *current_b, int operation_to_do){
  char dimention[128];
  
  switch(switcher){
    case '\0':
      get_new_line(line, room_file);
      master_switch(switcher, line, room_file, current_r, current_b, 0);
      break;

    case '+':
      if (operation_to_do == 1) {
        if(line[0] != '+')
          get_new_line(line, room_file);
        if (line[1] == '+') {
          for(int j = 2; j < sizeof(line) - 2; j++)
            dimention[j - 2] = line[j];
          sscanf(dimention, "%f", &current_b->height);
          get_new_line(line, room_file);
        }
        if(insert_corners(line, room_file, *current_b->corners, '+', dimention, -1) < 0)
          return -5;
        break;
      }
      if(line[0] != '+')
        get_new_line(line, room_file);
      if (line[1] == '+') {
        for(int j = 2; j < sizeof(line) - 2; j++)
          dimention[j - 2] = line[j];
        sscanf(dimention, "%f", &current_r->height);
        get_new_line(line, room_file);
      }
      if(insert_corners(line, room_file, *current_r->corners, '+', dimention, -1) < 0)
        return -5;
      break;

    case '-':
      if (operation_to_do == 1) {
        if(line[0] != '-')
          get_new_line(line, room_file);
        if(insert_corners(line, room_file, *current_b->corners, '-', dimention, -1) < 0)
          return -5;
      break;
      
      }
      if(line[0] != '-')
        get_new_line(line, room_file);
      if(insert_corners(line, room_file, *current_r->corners, '-', dimention, -1) < 0)
        return -5;
      break;

    case '/':
      if (operation_to_do == 1) {
        if(line[0] != '/')
          get_new_line(line, room_file);
        if(insert_corners(line, room_file, *current_r->corners, '/', dimention, 1) < 0)
          return -5;
        break;
      }
      if(line[0] != '/')
        get_new_line(line, room_file);
      if(insert_corners(line, room_file, *current_r->corners, '/', dimention, 1) < 0)
        return -5;
      break;

    case '@':
      if(get_first_line(line, current_r->name, room_file, ROOM_STARTER) < 0)
        return -21;

      int len1;
      int len2;
  
      if(get_sep_spacing(&len1, &len2, line, 4, SEPERATOR) < 0)
        return -31;

      current_r->room_number = get_number(&len1, &len2, line);
      if(current_r->room_number < 0)
        return -41;

      //set room format from the char after the last SEPERATOR
      current_r->room_format = line[len2 + 1];
      //printf("%s, %c, %d\n", rp.name, rp.room_format, rp.room_number);
      get_new_line(line, room_file);
      master_switch(current_r->room_format, line, room_file, current_r, current_b, 0);

      //print_room(current_r);

      if (line[0] == '#') {
        master_switch(line[0], line, room_file, current_r, current_b, 0);
        break;
      }
      master_switch(line[0], line, room_file, current_r, current_b, 0);
      break;

    case '#':
      if (operation_to_do == 0) {
        current_b = append_box_to_room(current_r);
      }
      else if (operation_to_do == 1) {
        current_b = append_new_box(current_b);
      }
      else if (operation_to_do == -1) {
        current_b = go_level_down_box(current_b);
      }

      if(get_first_line(line, current_b->name, room_file, BOX_STARTER) < 0)
        return -22;

      if(get_sep_spacing(&len1, &len2, line, 4, SEPERATOR) < 0)
        return -32;

      current_b->box_number = get_number(&len1, &len2, line);
      if(current_b->box_number < 0)
        return -41;

      current_b->box_format = line[len2 + 1];

      get_new_line(line, room_file);
      get_description(line, room_file, current_b->description);

      {
      char dimention_m[128] = { 0 };
      get_new_line(line, room_file);
      insert_corners(line, room_file, (float*)current_b->location, '<', dimention_m, 1);
      }
      insert_corners(line, room_file, (float*)current_b->corners, current_b->box_format, dimention, MAX_SEARCH);

      //print_box(current_b);

      if (line[0] == '>') {
        master_switch('>', line, room_file, current_r, current_b, -1);
        break;
      }
      else if (line[0] == '#') {
        master_switch('#', line, room_file, current_r, current_b, 1);
        break;
      }
      else {
        master_switch(line[0], line, room_file, current_r, current_b, 0);
        break;
      }

    case '>':
      {
      obj *current_o;
      if (operation_to_do == -1) {
        current_o = put_object_in_box(current_b);
      }
      else if (operation_to_do == 0) {
        current_o = put_object_next_to_box(current_b);
      }
      else {
        return -1;
      }

      if(get_first_line(line, current_o->name, room_file, OBJECT_STARTER) < 0)
        return -22;

      if(get_sep_spacing(&len1, &len2, line, 4, SEPERATOR) < 0)
        return -32;

      current_o->object_number = get_number(&len1, &len2, line);
      if(current_o->object_number < 0)
        return -41;

      get_new_line(line, room_file);
      get_description(line, room_file, current_o->description);

      {
      char dimention_o[128] = { 0 };
      get_new_line(line, room_file);
      insert_corners(line, room_file, (float*)current_o->location, '<', dimention_o, 1);
      }
      //print_obj(current_o);
      }
      master_switch(line[0], line, room_file, current_r, current_b, 0);

      break;

    case '{':
      get_new_line(line, room_file);
      master_switch(line[0], line, room_file, current_r, current_b, -1);

      break;
    case '}':
      get_new_line(line, room_file);
      master_switch(line[0], line, room_file, current_r, go_level_up_box(current_b), 1);

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
    for (int i = 0; i < DESCRIBE_SIZE - 1 && line[i] != '\0'; i++) {
      description[i] = line[i + 1];
      description[i + 1] = '\0';
    }
    return 0;
  }
  return -1;
}

int get_first_line(char *line, char *name, FILE *room_file, char STARTER){
  //get new lines if they dont start with room starter
  while (line[0] != STARTER){
    fgets(line, 128, room_file);
  }

  //we just checked if the line starts with line starter
  //we just copy the name portion of the line to the name variable of the room struct
  for(int i = 1; line[i] != SEPERATOR; i++){
    name[i - 1] = line[i];
    //if the name in file is to long we stop the reading
    if(i > NAME_SIZE - 2) return -1;
  }
  return 0;
}

int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN, char seperator){
  for (*len1 = 1; line[*len1] != seperator && *len1 < MAX_SEARCH; *len1+=1);
  for (*len2 = *len1 + 1; line[*len2] != seperator && *len2 < (MAX_SEARCH - *len1); *len2+=1);

  //set the stuff betwen the SEPERATORs to the number of the room
  if(*len2 - *len1 > MAX_LEN + 1)
    return -1;
  return 0;
}

int get_number(int *len1, int *len2, char *line){
  int number = 0;
  char room_num[4] = { 0 };
  number = 0;
  for(int i = 1; i <= *len2 - (*len1 + 1); i++){
    number *= 10;
    number += (line[*len1 + i] - '0');
  }
  return number;
}

int get_new_line(char *line, FILE *room_file){
  memset(line, 0, MAX_SEARCH);
  fgets(line, MAX_SEARCH, room_file);
  return 0;
}

int insert_corners(char *line, FILE *room_file, float *corners, char format, char *dimention, int max_size){

  if (max_size < 0)
    max_size = -1 * (max_size * MAX_SEARCH);

  for(int i = 0; line[0] == format; i++){

    if(i > max_size - 1)
      return -1;

    int t_len[2];
    get_sep_spacing(&t_len[0], &t_len[1], line, -1, format);

    //printf("%c, %c, %c", line[0], line[t_len[0]], line[t_len[1]]);

    memset(dimention, 0, 128);
    for(int j = 1; j < t_len[0]; j++)
      dimention[j - 1] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i));
    memset(dimention, 0, 128);
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    for(int j = t_len[0] + 1; j < t_len[1]; j++)
      dimention[j - (1 + t_len[0])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i + 1 ));
    memset(dimention, 0, 128);
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    for(int j = t_len[1] + 1; j < MAX_SEARCH - 1; j++)
      dimention[j - (1 + t_len[1])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i + 2));
    memset(dimention, 0, 128);
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    /*
    printf("x:%f\n", *(&corners[0]));
    printf("y:%f\n", *(&corners[0] + 1));
    printf("z:%f\n", *(&corners[0] + 2));
    printf("\n");
    */

    get_new_line(line, room_file);

    if(line[1] == format)
      return 1;

  }
  return 0;
}

/*
int master_switch(char format, char *line, FILE *room_file, float *height, float *corners){
  char dimention[128];
  switch (format) {

    case '+': //for handling corners + corner

      if(line[0] != '+')
        get_new_line(line, room_file);

      //getting the height
      if (line[1] == format) {
        for(int j = 2; j < sizeof(line) - 2; j++)
          dimention[j - 2] = line[j];

        sscanf(dimention, "%f", height);

        get_new_line(line, room_file);

        //printf("height:%f\n\n", *height);
      }

      if(insert_corners(line, room_file, corners, '+', dimention, -1) < 0)
        return -5;

      break;

    case '-': //for handling just dimentions input
      if(line[0] != '-')
        get_new_line(line, room_file);
      if(insert_corners(line, room_file, corners, '-', dimention, -1) < 0)
        return -5;
      break;

    case '/': //for handling size input
      if(line[0] != '/')
        get_new_line(line, room_file);
      if(insert_corners(line, room_file, corners, '/', dimention, 1) < 0)
        return -5;
      break;

      default:
        return -6;
  }
  return 0;
}
*/
