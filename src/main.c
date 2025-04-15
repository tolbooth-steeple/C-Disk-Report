#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

// declare functions here
long get_file_size(char *);
long get_file_size_linux(char *);
int is_old_file(char *);


// start of program
int main() {
  char *filename = "example.txt";
  char *old_filename = "/mnt/c/Users/Jeff/Desktop/digital forensics papers.txt";
  long filesize = get_file_size(filename);
  printf("Using naive solution: size of '%s' is %ld\n", filename, filesize);
  filesize = get_file_size_linux(filename);
  printf("Using Linux API: size of '%s' is %ld\n", filename, filesize);


  // is example.txt old?
  printf("Is file '%s' old? (More likely to be obsolete): %i\n", filename, is_old_file(filename));
  // 
  printf("Is file '%s' old? (More likely to be obsolete): %i\n", old_filename, is_old_file(old_filename));
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


int is_old_file(char *filename) {
  // initialise var to contain file information
  struct stat file_info;
  // generate stat structure for filename and store at address of file_info
  stat(filename, &file_info);

  // according to documentation, times given in seconds since Epoch (time_t)
  // define 'old' as more than a year
  // 1 year in seconds is 365*24*60*60
  int year = 365*24*60*60;
  time_t now = time(NULL);
  int old_threshold = now - year;
  // if file has been accessed, modified or otherwise had it's status changed before threshold, it's old
  if ((old_threshold > file_info.st_atime) || (old_threshold > file_info.st_ctime) || (old_threshold > file_info.st_mtime )) {
    return 1;
  }
  return 0;
}