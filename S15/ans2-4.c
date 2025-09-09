#include <stdio.h>
#include <string.h>
struct student {
	char number[10]; //学籍番号
	char name[64];   //名前
};
void write(struct student *data)
{
	strcpy(data->number,"K024C9902");
	strcpy(data->name,"工学院八王子");
}
void disp(struct student *data)
{
	printf("number: %s\n",data->number);
	printf("name: %s\n",data->name);
}

int main(void)
{
	struct student data[2];
	
	strcpy(data[0].   number,"K024C9901");
	strcpy(data[0].   name,"工学院蒲田");
	write(data+1);
	disp(data+0);
	disp(data+1);
}	
