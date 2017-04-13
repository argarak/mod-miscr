
#include "move.h"
#include "../../../control/stepper.h"

int strcmp(const char* s1, const char* s2) {
  while(*s1 && (*s1 == *s2))
      s1++; s2++;
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int GCodeG0(char* a[], int l, char* rp, char* op) {
  if(strcmp(a[0], "G0") != 0)
    return 1;

  for(int i = 0; i < l; i++) {
    switch(a[i][0]) {
    case 'X':
      break;
    }
  }
}

int GCodeG1(char* a[], int l, char* rp, char* op) {
  
}
