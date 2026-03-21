#include "config.h"
#include <cstdio>
#include <cstring>

void delete_box(box* to_delete){
  if (to_delete == NULL) {
    return;
  }
  obj* temp_o = to_delete->first;
  to_delete->first = NULL;
  obj* temp_oo;
  while (temp_o != NULL) {
    temp_oo = temp_o->next;
    delete temp_o;
    temp_o = temp_oo;
  }
  box * temp_n = to_delete->next;
  if (temp_n != NULL) {
    delete_box(temp_n);
  }
  box* temp_i = to_delete->inner;
  if (temp_i != NULL) {
    delete_box(temp_i);
  }
  delete to_delete;
}

void delete_with_name(char *in, box* current){
  box* temp = current->inner;
  while (temp != NULL) {
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
      printf(RED "Are you sure you want to delete box \"%s\"?" RESET, temp->name);
      char confirm[2] = "N";
      scanf("%1s", confirm);
      if (confirm[0] == 'Y' || confirm[0] == 'y') {
        box* temp_bb = temp->prev->inner;
        if (temp_bb == temp) {
          temp->prev->inner = temp->next;
          delete_box(temp->inner);
          delete temp;
          return;
        }
        while (temp_bb->next != temp){
          temp_bb = temp_bb->next;
          if (temp_bb == NULL) {
            return;
          }
        }
        temp_bb->next = temp->next;
        delete_box(temp->inner);
        delete temp;
        return;
      }
      printf(YELLOW "Aborting!\n" RESET);
      return;
    }
  }
  obj* temp_o = current->first;
  while (temp_o != NULL) {
    int i;
    int ok = 1;
    for (i = 0; i < LINE_SIZE - 2 && in[ i + 1 ] != '\0'; i++){
      if (temp_o->name[i] != in[i + 2]) {
        temp_o = temp_o->next;
        ok = 0;
        break;
      }
    }
    if (ok == 1) {
      printf(RED "Are you sure you want to delete object \"%s\"?" RESET, temp_o->name);
      char confirm[2] = "N";
      scanf("%1s", confirm);
      if (confirm[0] == 'Y' || confirm[0] == 'y') {
        obj* temp_oo = temp_o->prev->first;
        if (temp_oo == temp_o) {
          temp_o->prev->first = temp_o->next;
          delete temp_o;
          return;
        }
        while (temp_oo->next != temp_o){
          temp_oo = temp_oo->next;
          if (temp_oo == NULL) {
            return;
          }
        }
        temp_oo->next = temp_o->next;
        delete temp_o;
        return;
      }
      printf(YELLOW "Aborting!\n" RESET);
      return;
    }
    else {
      printf(YELLOW "No such object or box found!\n" RESET);
      return;
    }
  }
}

void print_path_b(box *current){
  if (current->prev != NULL) {
    printf(MAGENTA "#%s" RESET "<", current->name);
    print_path_b(current->prev);
    return;
  }
  printf(MAGENTA "#%s\n" RESET, current->name);
}

void print_path_o(obj *current){
  printf(CYAN ">%s" RESET "<", current->name);
  print_path_b(current->prev);
}

void print_searched_under(char *in, box **current){
  if (current == NULL) {
    return;
  }
  box* temp = *current;
  int i;
  int ok = 1;
  for (i = 0; i < LINE_SIZE - 2 && in[ i + 2 ] != '\0'; i++){
    if (temp->name[i] != in[i + 2]) {
      temp = temp->next;
      ok = 0;
      break;
    }
  }
  if (ok == 1) {
    print_path_b(temp);
  }

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
  temp = (*current)->inner;
  if (temp != NULL) {
    print_searched_under(in, &temp);
  }
  box *temp_b = (*current)->next;
  if (temp_b != NULL) {
    print_searched_under(in, &temp_b);
  }
}

void print_stats_b(box* current){
  if (current == NULL) {
    return;
  }
  printf(YELLOW "Upper box:" MAGENTA " %s", current->prev->name);
  printf(YELLOW "\nRelative location in previous box:\n" MAGENTA "x: %f, y: %f, z: %f", current->location[0], current->location[1], current->location[2]);
  printf(YELLOW "\nDescription:" MAGENTA " %s", current->description);
  printf(YELLOW "Box format:" MAGENTA " %c", current->box_format);
  printf(YELLOW "\nCorners:\n" MAGENTA);
  for (int i = 0; i < 128 && current->corners[i][0] != '\0'; i++) {
    for (int j = 0; j < 3 && current->corners[i][j] != '\0'; j++){
      printf("%f", current->corners[i][j]);
      if (j != 2)
        printf(", ");
    }
    printf("\n");
  }
  printf("" RESET);

}

void print_stats_o(obj* current){
  if (current == NULL) {
    return;
  }
  printf(YELLOW "Upper box:" CYAN " %s", current->prev->name);
  printf(YELLOW "\nRelative location in previous box:" CYAN "\nx: %f, y: %f, z: %f", current->location[0], current->location[1], current->location[2]);
  printf(YELLOW "\nDescription:" CYAN " %s" RESET, current->description);
}

void print_atributes(box **current, char *in){
  if (current == NULL || *current == NULL) {
    return;
  }
  box* temp = (*current)->inner;
  while (temp != NULL){
    int i;
    int ok = 1;
    for (i = 0; i < LINE_SIZE - 3 && in[ i + 3 ] != '\0'; i++){
      if (temp->name[i] != in[i + 3]) {
        temp = temp->next;
        ok = 0;
        break;
      }
    }
    if ( ok == 1 ) {
      print_stats_b(temp);
      return;
    }
  }
  obj* temp_o = (*current)->first;
  while (temp_o != NULL){
    int i;
    int ok = 1;
    for (i = 0; i < LINE_SIZE - 3 && in[ i + 3 ] != '\0'; i++){
      if (temp_o->name[i] != in[i + 3]) {
        temp_o = temp_o->next;
        ok = 0;
        break;
      }
    }
    if ( ok == 1 ) {
      print_stats_o(temp_o);
      return;
    }
  }
}

void print_names(box *current){
  if (current == NULL) {
    return;
  }
  box* temp = current->inner;
  while (temp != NULL){
    printf(MAGENTA "#%s\n" RESET, temp->name);
    temp = temp->next;
  }
  obj* temp_o = current->first;
  while (temp_o != NULL) {
    printf(CYAN ">%s\n" RESET, temp_o->name);
    temp_o = temp_o->next;
  }
}

void new_object(box* current){

  char temp_obj[64] = "";

  printf(CYAN "Enter object name: " RESET);
  scanf("%63s", temp_obj);

  if (temp_obj[0] == 'q' && temp_obj[1] == '\0') {
    printf(YELLOW "Aborting!\n" RESET);
    return;
  }

  obj* temp_o = put_object_in_box(current);

  for (int i = 0; i < LINE_SIZE; i++) {
    temp_o->name[i] = temp_obj[i];
  }

  printf(CYAN "Enter object description: " RESET);
  scanf("%126s", temp_o->description);
  strcat(temp_o->description, "\n");

  printf(YELLOW "Enter relative location of object inside box:\n" RESET);
  printf(CYAN "x-coordinate: " RESET);
  scanf("%f", &temp_o->location[0]);
  printf(CYAN "y-coordinate: " RESET);
  scanf("%f", &temp_o->location[1]);
  printf(CYAN "z-coordinate: " RESET);
  scanf("%f", &temp_o->location[2]);

  return;
}

void new_box(box* current){
  
  char temp_name[64] = "";

  printf(MAGENTA "Enter box name: " RESET);
  scanf("%63s", temp_name);

  box* temp;

  if (temp_name[0] == 'q' && temp_name[1] == '\0') {
    printf(YELLOW "Aborting!\n" RESET);
    return;
  }
  if (current->inner != NULL) {
    temp = append_new_box(current->inner);
  }
  else {
    temp = new box();
    current->inner = temp;
  }

  for (int i = 0; i < LINE_SIZE; i++) {
    temp->name[i] = temp_name[i];
  }

  printf(MAGENTA "Enter box description: " RESET);
  scanf("%126s", temp->description);
  strcat(temp->description, "\n");

  printf(YELLOW "Enter relative location of box inside parent box:\n" RESET);
  printf(MAGENTA "x-coordinate: " RESET);
  scanf("%f", &temp->location[0]);
  printf(MAGENTA "y-coordinate: " RESET);
  scanf("%f", &temp->location[1]);
  printf(MAGENTA "z-coordinate: " RESET);
  scanf("%f", &temp->location[2]);

  printf(MAGENTA "Enter box format: " RESET);
  scanf("%s", &temp->box_format);

  while (temp->box_format != '+' && temp->box_format != '-' && temp->box_format != '/') {
    printf(RED "Invalid format!!\n" YELLOW "Enter anew: " RESET);
    scanf("%s", &temp->box_format);
  }

  if (temp->box_format == '+') {
    printf(MAGENTA "Enter box height: " RESET);
    scanf("%f", &temp->height);
  }


  printf(YELLOW "Start entering corners (max 127, when done set x-coordinate to -1): " RESET);
  int i;
  float temp_float;
  for (i = 0; i < 128; i++){
    printf(YELLOW "Corner no. %d: \n" RESET, i + 1);
    printf(MAGENTA "x-coordinate: " RESET);
    scanf("%f", &temp_float);
    if (temp_float == -1.0) {
      break;
    }
    temp->corners[i][0] = temp_float;
    printf(MAGENTA "y-coordinate: " RESET);
    scanf("%f", &temp->corners[i][1]);
    printf(MAGENTA "z-coordinate: " RESET);
    scanf("%f", &temp->corners[i][2]);
  }

  return;
}
