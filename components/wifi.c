#include <limits.h>
#include <linux/wireless.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include "coutil.h"

int wifi_perc(char *interface);


const char* wifi_signal(){
	int perc = wifi_perc("wlp3s0");	
	if(perc > 50)
		return " ";
	else if(perc > 5)
		return "直 ";
	else if(perc < 0) 
		return bprintf("%s %d" , "" , perc * -1 );
	else
		return "睊 ";
}

int wifi_perc(char *interface)
{
	int cur;
	size_t i;
	char *p, *datastart;
	char path[80];
	char status[5];
	FILE *fp;

	if (esnprintf(path, sizeof(path), "/sys/class/net/%s/operstate",
	              interface) < 0) {
		return -1; // PATH size isn't enough
	}
	if (!(fp = fopen(path, "r"))) {
		warn("fopen '%s':", path);
		return -2; // can't find Network card 
	}
	p = fgets(status, 5, fp);
	fclose(fp);
	if (!p || strcmp(status, "up\n") != 0) {
		return 0;
	}

	if (!(fp = fopen("/proc/net/wireless", "r"))) {
		warn("fopen '/proc/net/wireless':");
		return -4; // can't find this file
	}

	for (i = 0; i < 3; i++) {
		if (!(p = fgets(buf, sizeof(buf) - 1, fp)))
			break;
	}
	fclose(fp);
	if (i < 2 || !p) {
		return -5; // the first two lines are garbage
	}

	if (!(datastart = strstr(buf, interface))) {
		return -6; // well you card is not there
	}

	datastart = (datastart+(strlen(interface)+1));
	sscanf(datastart + 1, " %*d   %d  %*d  %*d\t\t  %*d\t   "
	       "%*d\t\t%*d\t\t %*d\t  %*d\t\t %*d", &cur);
	return cur;
}

const char *
wifi_essid(const char *interface)
{
	static char id[IW_ESSID_MAX_SIZE+1];
	int sockfd;
	struct iwreq wreq;

	memset(&wreq, 0, sizeof(struct iwreq));
	wreq.u.essid.length = IW_ESSID_MAX_SIZE+1;
	if (esnprintf(wreq.ifr_name, sizeof(wreq.ifr_name), "%s",
	              interface) < 0) {
		return NULL;
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		warn("socket 'AF_INET':");
		return NULL;
	}
	wreq.u.essid.pointer = id;
	if (ioctl(sockfd,SIOCGIWESSID, &wreq) < 0) {
		warn("ioctl 'SIOCGIWESSID':");
		close(sockfd);
		return NULL;
	}

	close(sockfd);

	if (!strcmp(id, "")) {
		return NULL;
	}

	return id;
}
