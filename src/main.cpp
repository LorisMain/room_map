#include <stdio.h>

int main(){
  char in[8] = { 0 };
  do{
    scanf("%s", &in[0]);
    printf("hallo, %s", in);
  } while(in[0] != 'q');
  return 0;
}
