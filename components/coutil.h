#include <stdint.h>
#include<stdio.h>

#define LEN(x) (sizeof (x) / sizeof *(x))

extern char buf[1024];

void getcmd(const char* command);

extern char *argv0;

void warn(const char *, ...);
void die(const char *, ...);

int esnprintf(char *str, size_t size, const char *fmt, ...);
const char *bprintf(const char *fmt, ...);
const char *fmt_human(uintmax_t num, int base);
int pscanf(const char *path, const char *fmt, ...);
void v_human(double* scaled,int* size);
void concat(char* buf,int bufsize,int argc,...);

