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
  do{

    //gets the first line and also sets the name of the room
    if(get_first_line(line, room_p.name, room_file, ROOM_STARTER) < 0)
      return -2;

    //getting the distance to the SEPERATORs
    int len1;
    int len2;
  
    if(get_sep_spacing(&len1, &len2, line, 4) < 0)
      return -3;

    room_p.room_number = get_number(&len1, &len2, line);
    if(room_p.room_number < 0)
      return -4;

    //set room format from the char after the last SEPERATOR
    room_p.room_format = line[len2 + 1];

    //reading dimentions
    char dimention[128];
    switch (room_p.room_format) {

      case '+': //for handling corners + corner

        get_new_line(line, room_file);

        for(int i = 0; line[0] == room_p.room_format; i++){
          if (line[1] == room_p.room_format) {

            for(int j = 2; j < sizeof(line) - 2; j++)
              dimention[j - 2] = line[j];

            sscanf(dimention, "%f", &room_p.height);

            i--;

            get_new_line(line, room_file);

            continue;
            //printf("%f\n", dimention);
          }

          if (i > 128)
            return -5;

          for(int j = 1; j < sizeof(line) - 1; j++)
            dimention[j - 1] = line[j];

          sscanf(dimention, "%f", &room_p.corners[i]);

          printf("%f\n", room_p.corners[i]);

          get_new_line(line, room_file);
        }

      case '-': //for handling just dimentions input
        if(insert_corners(line, room_file, &room_p.corners[0], '-', dimention, -1) < 0)
          return -5;

      case '/': //for handling size input
          if(insert_corners(line, room_file, &room_p.size[0], '/', dimention, 3) < 0)
            return -5;

        default:
          return -6;
    }
    printf("1");
    printf("%s\n", room_p.name);

    end = 1;

  }while(end == 0);


  return 0;
}

int get_first_line(char *line, char *name, FILE *room_file, char STARTER){
  //get new lines if they dont start with room starter
  do{
    fgets(line, 128, room_file);
  }while (line[0] != STARTER);

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

int get_sep_spacing(int *len1, int *len2, char *line, int MAX_LEN){
  for (*len1 = 0; line[*len1] != SEPERATOR && *len1 < MAX_SEARCH; *len1+=1);
  for (*len2 = *len1 + 1; line[*len2] != SEPERATOR && *len2 < (MAX_SEARCH - *len1); *len2+=1);

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
    max_size = MAX_SEARCH;

  for(int i = 0; line[0] == format; i++){

    if(i > max_size)
      return -1;

    for(int j = 1; j < sizeof(line) - 1; j++)
      dimention[j - 1] = line[j];

    sscanf(dimention, "%f", &corners[i]);

    printf("%f\n", corners[i]);

    get_new_line(line, room_file);
  }
  return 0;
}
