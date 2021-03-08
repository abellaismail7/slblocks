/* See LICENSE file for copyright and license details. */



typedef struct {
	char* (*func)(const char** args);
	unsigned int interval;
	unsigned int signal;
	const char** args;
} Block;

/* battery */
char* battery(const char** args);

/* ip */
char* ipv4(const char** args);
char* ipv6(const char** args);

/* date */
char* datetime(const char** args);

/* memory */
char* free_mem(const char** args);

/* disk */
char* disk_usage(const char** args);

/* Shell */
char* shell(const char** args);

/* Kernel */
char* kernel_release(const char** args);
char* hostname(const char** args);

/* Keymap */
char* keymap(const char** args);

/* CPU */
char* cpu_usage(const char** args);

/* tmp/cancalable proccess  */
char* loading(const char** args);

/* WIFI */
char* wifi_signal(const char ** args);
