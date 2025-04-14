#include <stdio.h>

// declare functions here
long get_file_size(char *);

// start of program
int main() {
  char *filename = "example.txt"
  long filesize = get_file_size(filename)
  printf("Size of '%s' is %ld", filename, filesize)
}