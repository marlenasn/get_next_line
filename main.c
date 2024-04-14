
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
	int fd;
	char* s;
	fd = open("plik.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("%s\n", s);
	s = get_next_line(fd);
	printf("%s\n", s);
	s = get_next_line(fd);
	printf("%s\n", s);
	return 0;
}
