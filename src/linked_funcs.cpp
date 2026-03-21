#include "config.h"

box *append_new_box(struct box *first){ //if first NULL return address of new_box else run till the end of boxes and append one
  if(first == NULL){
    return new box();
  }
  box *temp = first;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new box();
  temp->next->prev = first->prev;
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
    temp = temp->next;
  }
  temp->prev = current;
  return temp;
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

box *go_level_up_box(struct box *current){
  if (current == NULL) {
    return NULL;
  }
  if (current->prev == NULL) {
    return NULL;
  }
  return current->prev;
}
