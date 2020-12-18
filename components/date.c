#include <time.h>
#include "coutil.h"
/*** date 
 * args[0] is date format 
 * you could add icon too
 * ***/

char* date(char** args){
	time_t t ; 
    time( &t );  
    struct tm *tmp = localtime( &t );   
	strftime(buf,80,args[0], tmp);
	return buf;
}
