/* MAX LENGTH OF BLOCK */
#define MAXBLC 50

#include <stdio.h>
#include <string.h>
#include "components.h"
#include "components/coutil.h"
static const char unknown_str[] = "n/a";

char buf[];


const char* volar[] = {"0","volume"};
const char* keyar[] = {"0","keytoggle"};
const char* st1ar[] = {"0","menu"};

static const Block blocks[] = {
	/*Func*/			/*ival*/	/*Sig*/	/*Argements*/
	{ shell,			0,            4,	st1ar	},
	{ wifi_signal,		0,            4,	NULL 	},
	{ battery,			60,           0,	NULL   	},
	{ free_mem, 		5,            0,	NULL 	},	
	{ hostname, 		30,           0,	NULL 	},	
	{ cpu_usage, 		5,            0,	NULL	},	
	{ shell, 			0,            2,	volar	},	
	{ datetime,			30,           0,	NULL 	},
	{ shell,			0,            3,	keyar	}
};





