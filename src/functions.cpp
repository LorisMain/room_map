#include "config.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int makefile(FILE *room_file){
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

//int readfile(FILE *room_file, struct room, struct box, struct object){
int readfile(FILE *room_file){
  
  room_file = fopen(FILE_NAME, "r");
  if (room_file == NULL){
    fclose(room_file);
    return -1;
  }

  bool end = 0;
  char line[128];
  room room_p;
  box box_p;
  do{

    ////////////////
    //room setting//
    ////////////////

    //gets the first line and also sets the name of the room
    get_new_line(line, room_file);
    if(get_first_line(line, room_p.name, room_file, ROOM_STARTER) < 0)
      return -21;

    printf("%s:\n", room_p.name);

    //getting the distance to the SEPERATORs
    int len1;
    int len2;
  
    if(get_sep_spacing(&len1, &len2, line, 4, SEPERATOR) < 0)
      return -31;

    room_p.room_number = get_number(&len1, &len2, line);
    if(room_p.room_number < 0)
      return -41;

    //set room format from the char after the last SEPERATOR
    room_p.room_format = line[len2 + 1];

    if(master_switch(room_p.room_format, line, room_file, &room_p.height, (float*)room_p.corners) < 0)
      return -51;

    //reading dimentions
    //printf("1");
    //printf("%s\n", room_p.name);
    

    /////////////////
    //boxes setting//
    /////////////////

    //gets the first box line and also sets the name of the box
    if(get_first_line(line, box_p.name, room_file, BOX_STARTER) < 0)
      return -2;
    printf("%s:", box_p.name);

    end = 1;

  }while(end == 0);


  return 0;
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
    if(i > NAME_SIZE - 2)
      return -1;
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

  get_new_line(line, room_file);

  if (max_size < 0)
    max_size = -1 * (max_size * MAX_SEARCH);

  for(int i = 0; line[0] == format; i++){

    if(i > max_size - 1)
      return -1;

    int t_len[2];
    get_sep_spacing(&t_len[0], &t_len[1], line, -1, format);

    //printf("%c, %c, %c", line[0], line[t_len[0]], line[t_len[1]]);

    for(int j = 1; j < t_len[0]; j++)
      dimention[j - 1] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i));
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    for(int j = t_len[0] + 1; j < t_len[1]; j++)
      dimention[j - (1 + t_len[0])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i) + 1);
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    for(int j = t_len[1] + 1; j < MAX_SEARCH - 1; j++)
      dimention[j - (1 + t_len[1])] = line[j];
    sscanf(dimention, "%f", (&corners[0] + 3 * i) + 2);
    //printf("%s\n", dimention);
    //printf("%d, %d", t_len[0], t_len[1]);

    printf("%f\n", *(&corners[0] + 3 * i));
    printf("%f\n", *((&corners[0] + 3 * i) + 1));
    printf("%f\n", *((&corners[0] + 3 * i) + 2));

    get_new_line(line, room_file);
  }
  return 0;
}

int master_switch(char format, char *line, FILE *room_file, float *height, float *corners){
  char dimention[128];
  switch (format) {

    case '+': //for handling corners + corner

      get_new_line(line, room_file);

      for(int i = 0; line[0] == format; i++){
        if (line[1] == format) {

          for(int j = 2; j < sizeof(line) - 2; j++)
            dimention[j - 2] = line[j];

          sscanf(dimention, "%f", height);

          i--;

          get_new_line(line, room_file);

          continue;
          //printf("%f\n", dimention);
        }

        if (i > 128)
          return -5;

        for(int j = 1; j < sizeof(line) - 1; j++)
          dimention[j - 1] = line[j];

        sscanf(dimention, "%f", &corners[0]);

        printf("%f\n", corners[0]);

        get_new_line(line, room_file);
      }
      break;

    case '-': //for handling just dimentions input
      if(insert_corners(line, room_file, corners, '-', dimention, -1) < 0)
        return -5;
      break;

    case '/': //for handling size input
      if(insert_corners(line, room_file, corners, '/', dimention, 1) < 0)
        return -5;
      break;

      default:
        return -6;
  }
  return 0;
}
