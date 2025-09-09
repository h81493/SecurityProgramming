#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
	FILE *fp;
	char buf[8192];
	char *c;
	int line_no;
	
	fp = fopen(argv[1],"r");
	if (fp == NULL) {
		printf("Can't open file\n");
		return -1;
	}
	line_no=1;
	while((fgets(buf,sizeof(buf),fp)) != NULL) {
		c = strchr(buf, '\n');
		if(c != NULL) {
			*c = '\0';
		}
		printf("%4d:%s\n",line_no++,buf);
	}
	fclose(fp);
	return 0;
}
