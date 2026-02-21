#include "config.h"
room *append_new_room(struct room *first){ //if NULL return address of new_room else run till end of rooms and append one
  if(first == NULL){
    return new room();
  }
  room *temp = first;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new room();
  return temp->next;
}

box *append_new_box(struct box *first){ //if first NULL return address of new_box else run till the end of boxes and append one
  if(first == NULL){
    return new box();
  }
  box *temp = first;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new box();
  return temp->next;
}

box *go_level_down_box(struct box *current){ //if current NULL return NULL else run till the end of inner boxes and append one
  if(current == NULL)
    return NULL;
  if(current->inner == NULL){
    current->inner = new box();
    current->inner->prev = current;
    return current->inner;
  }
  box *temp = current->inner;
  while(temp->next != NULL){
    temp->next->prev = temp;
    temp = temp->next;
  }
  return temp;
}

box *append_box_to_room(struct room *current){ //if current NULL return NULL else run till the end of boxes and append box
  if(current == NULL)
    return NULL;
  if(current->first == NULL){
    current->first = new box();
    return current->first;
  }
  box *temp = current->first;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new box();
  temp->next->prev = temp;
  return temp->next;
}

obj *put_object_next_to_box(struct box *current){ //if current box is NULL return address of new_obj else run till the end of objects and append new object  at the end
  if (current == NULL) {
    return new obj();
  }
  if (current->first == NULL) {
    current->first = new obj();
    return current->first;
  }
  obj *temp = current->first;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = new obj();
  return temp->next;
}

obj *put_object_in_box(struct box *current){
  if (current == NULL) {
    return NULL;
  }
  if (current->first == NULL) {
    current->first = new obj();
    current->first->prev = current;
    return current->first;
  }
  obj *temp = current->first;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = new obj();
  temp->next->prev = current;
  return temp->next;
}

box *go_level_down(struct box *current){
  if (current == NULL)
    return NULL;
  if (current->inner == NULL)
    return NULL;
  return current->inner;
}

box *go_level_up_box(struct box *current){
  if (current == NULL) {
    return NULL;
  }
  if (current->prev == NULL) {
    return NULL;
  }
  return current->prev;
}

/*
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
}
*/
