#include<stdio.h>

char* getcmd(const char* command,char** box){
	FILE *fp;
	fp = popen(command, "r");
	
	if(!fp)
		return "NULL";

   	fgets( *box, 20, fp);
   
   	pclose(fp);
}
