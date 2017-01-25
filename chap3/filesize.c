/* filesize.c - prints size of passwd file */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


int main()
{
	struct stat infobuf;
	if (stat("/etc/passwd", &infobuf) == -1)
		perror("/etc/passwd");
	else
		printf("The size of /etc/passwd is %d\n", (unsigned)infobuf.st_size);
} 
