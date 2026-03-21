#include "config.h"
#include <cstddef>
#include <stdio.h>
#include <cstdio>

FILE *new_file;
char f_name[64] = "";

int main(){

  box *master_box = new box();
  
  char line[LINE_SIZE];
  char in[LINE_SIZE] = { 0 };

  printf(GREEN "ENTER COMMAND> " RESET);
  scanf("%62s", in);
  box* location = master_box;
  box** for_switch = &location;
  while(in[0] != 'q'){
    action_switch(in, for_switch, &master_box, line);
    printf(GREEN "ENTER COMMAND> " RESET);
    scanf("%62s", in);
  }

  new_file = fopen(f_name, "w");
  writefile(new_file, master_box);
  fclose(new_file);

  return 0;
}

int action_switch(char *in, box** current, box **master_box, char *line){
  switch (in[0]) {

    case 'd': //delete
      delete_with_name(in, *current);
      break;

    case 'f':
      {
      printf(YELLOW "Enter new file name: " RESET);
      scanf("%63s", f_name);
      makefile(f_name);
      new_file = fopen(f_name, "r");
      get_new_line(line, new_file);
      master_switch('1', line, new_file, *master_box);
      fclose(new_file);
      }
      break;

    case 'h': //help
      printf(BLUE "HELP_TEXT:\n" RESET);
      printf(YELLOW "%s" RESET, HELP_TEXT);
      break;
      
    case 'l': //list
      if ( in[1] == 's' ) {
        print_all_b(*current);
        printf(RED);
        for(int i = 0; i < LINE_SIZE/2; i++)
          printf("_");
        printf("\n" RESET);
      }
      else if ( in[1] == 'a' ) {
        print_atributes(current, in);
      
      }
      else {
        //print only names
        print_names(*current);
      }
      break;
      
    case 'm': //move
      if (in[1] == 'b') {
        if ((*current)->prev != NULL) {
          (*current) = (*current)->prev;
        }
        else {
          printf(YELLOW "Already at the root\n" RESET);
        }
        return 0;
      }
      {
      box* temp = (*current)->inner;
      if (temp == NULL) {
        printf(RED "Nowhere to move to!\n" RESET);
      }
      while (temp != NULL){
        int i;
        int ok = 1;
        for (i = 0; i < LINE_SIZE - 2 && in[ i + 1 ] != '\0'; i++){
          if (temp->name[i] != in[i + 2]) {
            temp = temp->next;
            ok = 0;
            break;
          }
        }
        if (ok == 1) {
          *current = temp;
          return 0;
          break;
        }
      }
      printf(YELLOW "Box does not exist\n" RESET);
      }
      break;

    case 'n': //new
      if (in[1] == 'o') {
        new_object(*current);
      }
      else {
        new_box(*current);
      }
      break;

    case 's': //search
      if ((*current)->inner == NULL) { //add first object printing of path
        break;
      }
      {
      obj *temp_o = (*current)->first;
      while (temp_o != NULL) {
        int i;
        int ok = 1;
        for (i = 0; i < LINE_SIZE - 2 && in[ i + 2 ] != '\0'; i++){
          if (temp_o->name[i] != in[i + 2]) {
            temp_o = temp_o->next;
            ok = 0;
            break;
          }
        }
        if (ok == 1) {
          print_path_o(temp_o);
          temp_o = temp_o->next;
        }
      }
      }
      print_searched_under(in, &(*current)->inner);
      break;

    default:
      return -1;
      break;
  }
  return 0;
}

    /*
    case 'a': //append
      break;

      if there will be time
    case 'c': //copy
      break;
      */

      /*
    case 'o': //open
      break;

      if there will be time
    case 'p': //paste
      break;
      */
