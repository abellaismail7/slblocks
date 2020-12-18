#include "coutil.h"
#include "stdlib.h"
#include "string.h"
/****
 * args[0] : "0" return value "1" send click signal
 * args[1] : sh command
 ****/

char* shell(char** args){
	if(args[0][0] == '1'){
		// prevent inifinity signal
		args[0] = "0";

		char cmd[50];
		strcpy(cmd,args[1]);
		strcat(cmd," ui");
		system(cmd);
		
	}
	getcmd(args[1]);

	return buf;

}
