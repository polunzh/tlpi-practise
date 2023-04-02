#include <stdio.h>
#include <stdlib.h>
#include <tlpi_hdr.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int srcFd, dstFd;
  char *buf;
  int BUFFER_SIZE = 1024;
  ssize_t numRead, numWrite;

  if (argc != 3)
  {
    usageErr("%s SOURCE DEST\n", argv[0]);
  }

  srcFd = open(argv[1], O_RDONLY);
  if (srcFd == -1)
  {
    errExit("open source file");
  }

  dstFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw_rw_rw_*/

  if (dstFd == -1)
  {
    errExit("open destination file");
  }

  while (true)
  {
    buf = malloc(BUFFER_SIZE);

    numRead = read(srcFd, buf, BUFFER_SIZE);
    if (numRead == -1)
    {
      errExit("read from source file");
    }

    if (numRead == 0)
    {
      break;
    }

    numWrite = write(dstFd, buf, numRead);
    if (numWrite != numRead)
    {
      errExit("write to destination file");
    }

    free(buf);
  }
  
  close(srcFd);
  close(dstFd);

  exit(EXIT_SUCCESS);
}