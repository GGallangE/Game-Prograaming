#include <stdio.h>
#include <string.h>
#include <ctype.h>

void Palindrome (char string[]);
void RemoveSpace (char *str);

int main() {
	char string[100];
	int leng = 0;
	
	printf("문자열을 입력하세요:");
	gets(string);
	RemoveSpace(string);
	Palindrome(string);
	return 0;
} 

void Palindrome(char string[]){
	int i;
    	int j=0;
	int length;
	
	length = strlen(string);
	for(i = 0 ; i < length/2; i++) {
		if(string[i] != string[length - 1 - i]) {
			j = 1;
		}
	}
	if(j==0) {
		printf("회문입니다");
	}
	else {
		printf("회문이 아닙니다");
	} 
}

void RemoveSpace(char *str) {
	char *d = str;
	do {
		while(isspace(*d)) {
			++d;
		}
		*str++ = *d++;
	} while(*str != '\0');
}
