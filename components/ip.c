#include <stdio.h>
#include <unistd.h>
#include <string.h>
#if defined(__OpenBSD__)
	#include <sys/types.h>
#elif defined(__FreeBSD__)
	#include <netinet/in.h>
#endif
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include "coutil.h"

const char* ip(const char* interface, unsigned short sa_family,char* fmt)
{
	struct ifaddrs *ifaddr, *ifa;
	int s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) < 0) {
		warn("getifaddrs:");
		return NULL;
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr) {
			continue;
		}
		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in6),
		                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		if (!strcmp(ifa->ifa_name, interface) &&
		    (ifa->ifa_addr->sa_family == sa_family)) {
			freeifaddrs(ifaddr);
			if (s != 0) {
				warn("getnameinfo: %s", gai_strerror(s));
				return NULL;
			}
			return bprintf(fmt, host);
		}
	}

	freeifaddrs(ifaddr);

	return NULL;

}


const char * ipv4(const char **args){
	return ip("wlp3s0", AF_INET,"IP: %s");
}

const char *ipv6(const char **args){
	return ip("wlp3s0", AF_INET6,"IP: %s");
}
