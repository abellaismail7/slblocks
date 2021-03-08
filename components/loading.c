#include "coutil.h"
#include<stdio.h>
/*** 
 * ***/

/* char* loading(char** args){
	FILE *fptr;
	fptr = fopen("/tmp/loading","r");
	if(fptr == NULL){
	  return "n/a";
	}

	char c;
	int lines = 0;
	int cur = 0;
	while((c = fgetc(fptr)) && c != EOF ){
		if(c == '\n'){
			lines++;
		}
		if(lines == 0){
			buf[cur++] = c;	
		}
	}
	buf[cur++] = '+';
	buf[cur++] = lines + '0';
	buf[cur++] = '\0';

	fclose(fptr);
	return buf;
} */


char* loading(char** args){
	getcmd("awk '{printf \"%s \",$3}' /tmp/loading");
	return buf;
}
