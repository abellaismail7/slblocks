#define LEN(x) (sizeof (x) / sizeof *(x))

extern char buf[1024];

void getcmd(const char* command);

void warn(const char *, ...);
void die(const char *, ...);

