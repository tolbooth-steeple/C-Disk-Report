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
  fseek(fileptr, 0, SEEK_END);

  long size = ftell(fileptr);

  // close the file before returning
  fclose(fileptr);
  return size;
}

// linux solution: use os API for file status
long get_file_size_linux(char *filename) {
  // initialise var to contain file information
  struct stat file_info;
  // generate stat structure for filename and store at address of file_info
  stat(filename, &file_info);
  return file_info.st_size;
}
