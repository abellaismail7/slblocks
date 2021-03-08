#include <time.h>
#include "coutil.h"
/*** date 
 * args[0] is date format 
 * you could add icon too
 * ***/


const char *
datetime(void)
{
	time_t t;

	time(&t);
	if (!strftime(buf, sizeof(buf), " %a %b %d %H:%M" , localtime(&t))) {
		warn("strftime: Result string exceeds buffer size");
		return "";
	}

	return buf;
}
