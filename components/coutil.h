
#define LEN(x) (sizeof (x) / sizeof *(x))

#ifndef buf
char buf[1024];
#endif


void getcmd(const char* command);

void warn(const char *, ...);
void die(const char *, ...);

