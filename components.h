/* See LICENSE file for copyright and license details. */



typedef struct {
	char* (*func)(const char** args);
	unsigned int interval;
	unsigned int signal;
	const char** args;
} Block;

/* battery */
char* battery_perc(const char** args);

/* ip */
char* ipv4(const char** args);
char* ipv6(const char** args);

/* date */
char* date(const char** args);

/* memory */
char* free_mem(const char** args);


/* Shell */
char* shell(const char** args);

/* Keymap */
char* keymap(const char** args);

/* CPU */
char* cpu_perc(const char** args);
