#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include "coutil.h"

const char* ip(const char* interface, unsigned short sa_family)
{
    int fd;
    struct ifreq ifr;

    /*AF_INET - to define network interface IPv4*/
    /*Creating soket for it.*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /*AF_INET - to define IPv4 Address type.*/
    ifr.ifr_addr.sa_family = sa_family;

    /*eth0 - define the ifr_name - port name
    where network attached.*/
    memcpy(ifr.ifr_name, interface, IFNAMSIZ-1);

    /*Accessing network interface information by
    passing address using ioctl.*/
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*closing fd*/
    close(fd);

    /*Extract IP Address*/
    strcpy(buf,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
	return buf;

}


const char * ipv4(const char **args){
	return ip(args[0], AF_INET);
}

const char *ipv6(const char **args){
	return ip(args[0], AF_INET6);
}
