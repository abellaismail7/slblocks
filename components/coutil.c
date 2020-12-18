#include <stdio.h>
#include "coutil.h"
#include <stdarg.h>
#include <stdlib.h>
void getcmd(const char* command){
	FILE *fp;
	fp = popen(command, "r");
	
	if(!fp)
		return;

   	fgets(buf, 20, fp);
   
   	pclose(fp);
}

void
warn(const char *fmt, ...){
	// not implemented
}

void
die(const char *fmt, ...)
{
	// not implemented yet
	exit(1);
}

