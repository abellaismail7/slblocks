/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "coutil.h"


int
pscanf(const char *path, const char *fmt, ...)
{
	FILE *fp;
	va_list ap;
	int n;

	if (!(fp = fopen(path, "r"))) {
		warn("fopen '%s':", path);
		return -1;
	}
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);

	return (n == EOF) ? -1 : n;
}




const char *
cpu_perc(char** args)
{
	static long double a[7];
	long double b[7], sum;
	printf("HEYYY you MF \n");
	memcpy(b, a, sizeof(b));
	/* cpu user nice system idle iowait irq softirq */
	if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
	           &a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6])
	    != 7) {
		return NULL;
	}
	if (b[0] == 0) {
		return NULL;
	}

	sum = (b[0] + b[1] + b[2] + b[3] + b[4] + b[5] + b[6]) -
	      (a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6]);

	if (sum == 0) {
		return NULL;
	}
	int r =  (int)(100 *
	               ((b[0] + b[1] + b[2] + b[5] + b[6]) -
	                (a[0] + a[1] + a[2] + a[5] + a[6])) / sum);
	printf("CPU : %d",r);
	sprintf(buf,"%d",r);
	return buf;
}








