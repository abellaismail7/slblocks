/* MAX LENGTH OF BLOCK */
#define MAXBLC 50

extern const char BUF [ MAXBLC ];
#include <stdio.h>
#include <string.h>
#include "components.h"
#include "components/coutil.h"
static const char unknown_str[] = "n/a";


char* dwm(const char** args){
	strcpy(buf,args[0]);
	return buf;
}


const char* bat_ar[] = { "BAT0","","","","" };
const char* ipar[] = {"wlp3s0"};
const char* datear[] = {" %a %b %d %H:%M"};
const char* mem_ar[] = {""};
const char* volar[] = {"0","volume"};
const char* keyar[] = {"0","keytoggle"};
const char* st1ar[] = {"dwm "};

static const Block blocks[] = {
	/*Func*/			/*ival*/	/*Sig*/	/*Argements*/
	{ battery_perc,		60,           0,	bat_ar					     	},
	{ free_mem, 		5,            0,	mem_ar							},	
	{ shell, 			0,            2,	volar							},	
	{ date,				30,           0,	datear							},
	{ shell,			0,            3,	keyar							},
	{ dwm,				1,            0,	st1ar							}
};





