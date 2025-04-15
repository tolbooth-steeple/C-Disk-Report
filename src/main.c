#include <stdio.h>
#include <sys/stat.h>

// declare functions here
long get_file_size(char *);

// start of program
int main() {
  char *filename = "example.txt";
  long filesize = get_file_size(filename);
  printf("Size of '%s' is %ld", filename, filesize);
}

// naive solution to get file size
// read till end of file, then return the number of bytes read
// tutorials online demonstrate with fseek, ftell built-in functions
long get_file_size(char *filename) {
  // open the given file in read mode
  FILE *fileptr = fopen(filename, "r");

  long size = ftell(fileptr);

  // close the file before returning
  fclose(fileptr);
  return size;
}

// linux solution: use os API for file status
long get_file_size_linux(char *filename) {
  // get file information with stat structure
  struct stat file_info;

  return file_info.st_size;
}
