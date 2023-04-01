#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <tlpi_hdr.h>

int main(int argc, char *argv[])
{
  char c;
  char *filename;
  int fd, opt, flag_append;
  int open_file_flag;

  while ((opt = getopt(argc, argv, ":a")) != -1)
  {
    switch (opt)
    {
    case 'a':
      flag_append = 1;
      break;

    default:
      break;
    }
  }

  if (optind > argc - 1)
  {
    usageErr("Usage: %s [-a] <filename>\n", argv[0]);
  }

  filename = argv[optind];

  open_file_flag = O_RDWR | O_CREAT;
  if (flag_append == 0)
  {
    open_file_flag |= O_TRUNC;
  } else {
    open_file_flag |= O_APPEND;
  }

  fd = open(filename, open_file_flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if (fd == -1)
  {
    usageErr("Open file %s failed\n", filename);
    exit(EXIT_FAILURE);
  }

  while ((c = getchar()) != 3)
  {
    fprintf(stdout, "%c", c);
    write(fd, &c, strlen(&c));
  }

  if (close(fd) == -1)
  {
    errExit("close");
  }

  return 0;
}
