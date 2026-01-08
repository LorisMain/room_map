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

    //get new lines if they dont start with room starter
    do{
      fgets(line, 128, room_file);
    }while (line[0] != ROOM_STARTER);

    //we just checked if the line starts with line starter
    //we just copy the name portion of the line to the name variable of the room struct
    for(int i = 1; line[i] != SEPERATOR; i++){
      room_p.name[i - 1] = line[i];
      //if the name in file is to long we stop the reading
      if(i > NAME_SIZE - 2)
        break;
    }

    //getting the distance to the SEPERATORs
    int len1;
    int len2;
    
    for (len1 = 0; line[len1] != SEPERATOR && len1 < MAX_SEARCH; len1++);
    for (len2 = len1 + 1; line[len2] != SEPERATOR && len2 < (MAX_SEARCH - len1); len2++);

    //set the stuff betwen the SEPERATORs to the number of the room
    if(len2 - len1 > 5)
      return -2;

    char room_num[4] = { 0 };
    room_p.room_number = 0;
    for(int i = 1; i <= len2 - (len1 + 1); i++){
      room_p.room_number *= 10;
      room_p.room_number += (line[len1 + i] - '0');
    }

    room_p.room_format = line[len2 + 1];

    //reading dimentions
    char height[128];
    switch (room_p.room_format) {
      case '+': //for handling corners + height
        memset(line, 0, 128);
        fgets(line, 128, room_file);
        for(int i = 0; line[0] == room_p.room_format; i++){
          if (line[1] == room_p.room_format) {
            for(int j = 2; j < sizeof(line) - 2; j++)
              height[j - 2] = line[j];
            sscanf(height, "%f", &room_p.height);
            i--;
            memset(line, 0, 128);
            fgets(line, 128, room_file);
            continue;
            //printf("%f\n", height);
          }
          for(int j = 1; j < sizeof(line) - 1; j++)
            height[j - 1] = line[j];
          sscanf(height, "%f", &room_p.corners[i]);
          printf("%f\n", room_p.corners[i]);
          memset(line, 0, 128);
          fgets(line, 128, room_file);
      }
      case '-': //for handling just corners input
        memset(line, 0, 128);
        fgets(line, 128, room_file);
        for(int i = 0; line[0] == room_p.room_format; i++){
          for(int j = 1; j < sizeof(line) - 1; j++)
            height[j - 1] = line[j];
          sscanf(height, "%f", &room_p.corners[i]);
          printf("%f\n", room_p.corners[i]);
          memset(line, 0, 128);
          fgets(line, 128, room_file);
        }
      case '/': //for handling size input
        memset(line, 0, 128);
        fgets(line, 128, room_file);
        for(int i = 0; line[0] == room_p.room_format; i++){
          for(int j = 1; j < sizeof(line) - 1; j++)
            height[j - 1] = line[j];
          sscanf(height, "%f", &room_p.size[i]);
          printf("%f\n", room_p.size[i]);
          memset(line, 0, 128);
          fgets(line, 128, room_file);
        }
        default:
          return -3;
    }
    printf("%s\n", room_p.name);

    end = 1;

  }while(end == 0);


  return 0;
}
