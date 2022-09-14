#include<stdio.h>
#include<stdlib.h>
int main(void){
	char ch;
	printf("문자를 입력하소 Enter> ");
	scanf("%c", &ch);
	system("cls");  //화면 지우기 
	printf("입력된 문자 %c\n",ch);
	return 0;
}
