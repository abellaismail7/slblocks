#include "../components.h"
#include<stdio.h>
typedef struct {
	const char* name;
	char* (*func)(const char** args);
	const char** args;
} Comp;


const char* args[] = { "BAT0","","","","" };
const char* ipar[] = {"wlp3s0"};
const char* datear[] = {"%a %b %d %H:%M"};
const char* mem_ar[] = {" M "};
const char* volume[] = {"0","volume"};
Comp components[] = {
	{ "battery", battery_perc, args },
	{ "ipv4", ipv4, ipar },
	{ "ipv6", ipv6, ipar },
	{ "date", date, datear },
	{ "free_mem", free_mem, mem_ar },
	{ "cpu_perc", cpu_perc, NULL },
	{ "volume", shell, NULL },
	{ "keymap", keymap, NULL }
};


