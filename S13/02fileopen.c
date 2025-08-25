#include <stdio.h>
#include <errno.h>
#include <string.h>

int main( void) {
	FILE *file;
	file = fopen("存在しないファイル.txt", "r");
	if(file == NULL) {
		perror("Error");
		fprintf(stderr, "%s(%d) %d:%s\n",__FILE__,__LINE__,errno,strerror(errno));
		return 1;
	}
	fclose(file);
	return 0;
}

