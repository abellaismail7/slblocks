/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <sys/statvfs.h>

#include "coutil.h"

double disk_free(const char *path);
int disk_perc(const char *path);
double disk_total(const char *path);
double disk_used(const char *path);


char* disk_usage(){
	double used = disk_used("/");
	int prefix = 1024;
	v_human(&used,&prefix);
	sprintf(buf,"%s %.1lf %ci","﫭", used,prefix);
	return buf;
}

double disk_free(const char *path)
{
	struct statvfs fs;

	if (statvfs(path, &fs) < 0) {
		warn("statvfs '%s':", path);
		return -1;
	}

	return fs.f_frsize * fs.f_bavail;
}

int disk_perc(const char *path)
{
	struct statvfs fs;

	if (statvfs(path, &fs) < 0) {
		warn("statvfs '%s':", path);
		return -1;
	}

	return (int)(100 *
	               (1.0f - ((float)fs.f_bavail / (float)fs.f_blocks)));
}

double disk_total(const char *path)
{
	struct statvfs fs;

	if (statvfs(path, &fs) < 0) {
		warn("statvfs '%s':", path);
		return -1;
	}
	return fs.f_frsize * fs.f_blocks;
}


double disk_used(const char *path)
{
	struct statvfs fs;

	if (statvfs(path, &fs) < 0) {
		warn("statvfs '%s':", path);
		return -1;
	}
	return fs.f_frsize * (fs.f_blocks - fs.f_bfree);
}
