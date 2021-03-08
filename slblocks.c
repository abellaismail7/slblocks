#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include <stdarg.h>
#define _XOPEN_SOURCE 700

#define LENGTH(X)               (sizeof(X) / sizeof (X[0]))
#define CMDLENGTH       50


#ifndef NO_X
#include<X11/Xlib.h>
#endif
#include "config.h"

static Display *dpy;
static int screen;
static Window root;

int setupX();
void updateBlock();
void signal_handler();
int setupSignals();
void writeStatus();
void block_check();
void statusloop();
void break_loop();
void button_handler();

int loopContinue = 1;
int sltime = 1;

static int block_length = LENGTH(blocks);
char* output;
char strs[LENGTH(blocks)][50];

int setupX(){
     dpy = XOpenDisplay(NULL);
     if (!dpy) {
         fprintf(stderr, "slblocks: Failed to open display\n");
         return 0;
     }
     screen = DefaultScreen(dpy);
     root = RootWindow(dpy, screen);
     return 1;
}



void button_handler(int sig, siginfo_t *si, void *ucontext){
	sig = si->si_value.sival_int >> 8;
	if(fork() == 0){
		const Block *current;
		for (int i = 0; i < LENGTH(blocks); i++){
			current = blocks + i;
			if (current->signal == sig){
				current->args[0] = "1";
				current->func(current->args);
				current->args[0] = "0";
				break;
			}
		}
	}
}

void updateBlock(int sig){
	// find block
	for(int i=0 ;i < block_length;i++){
		Block b = blocks[i];
		if(sig == b.signal){
			strcpy(strs[i], b.func(b.args) ); 
			break;
		}
	}
}

void signal_handler(int signum){
	updateBlock(signum-SIGRTMIN);
}

int setupSignals(){
	struct sigaction sa;

	sa.sa_handler = break_loop;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; 


	// DIE GRACEFULLY
    if (sigaction(SIGINT, &sa, NULL) == -1)
        return 0;
    if (sigaction(SIGTERM, &sa, NULL) == -1)
        return 0;



	sa.sa_handler = signal_handler;
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		int sig =blocks[i].signal;
	    if ( sig > 0 && sig+SIGRTMIN <= SIGRTMAX ){
    		sigaction(SIGRTMIN+sig, &sa, NULL);
		}
	}

	sa.sa_sigaction = button_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	return 1;
}



void writeStatus(){
	char* ststr = output;
	*(ststr++) = ' ';
	for(int i=0; i < block_length;i++){
		if(blocks[i].signal){
			*(ststr++) = blocks[i].signal;
		}
		
		const char* value = strs[i];
		while(*value){
			*(ststr++) = *value;
			value++;
		}
		if(i+1 != block_length){
			*(ststr++) = ' ';	
			*(ststr++) = '|';	
			*(ststr++) = ' ';	
		}
	}
	*(ststr++) = '\0';	
	if (1) {
		puts(output);
		fflush(stdout);
		if (ferror(stdout))
			die("puts:");
	} else {
		if (XStoreName(dpy, root, output)
                        < 0) {
			die("XStoreName: Allocation failed");
		}
		XFlush(dpy);
	}
}


void block_check(){

	for(int i=0; i < block_length;i++){
		
		Block block = blocks[i];
		// strcpy if interval is match time	
		if(block.interval != 0 && sltime % block.interval == 0)
			strcpy(strs[i],block.func(block.args));

	}
}

void block_check_first(){

	for(int i=0; i < block_length;i++){
		Block block = blocks[i];
		strcpy(strs[i],block.func(block.args));
	}
}


void statusloop(){
	block_check_first();
	while(1){
		block_check();
		writeStatus();	
		if(!loopContinue)
			break;
		sltime++;
		sleep(1.0);
	}

}
void break_loop(){
	write(1,"DIE DIE \n ",10);
	loopContinue = 0;
}

int main(){
    int i = system("pidof slblocks | grep -E \"^[0-9]*$\" > /dev/null "); 
	if(i != 0){
		puts("only one process is accepted");
		return 1;
	}
	if(!setupSignals()){
		return 1;
	}
	
	// READY TO alocations
	// setup X 
	if(!setupX()){
		return 1;
	}
	// NEED TO BE SCALEABLE # REALLOC 
	output = malloc(50 * block_length * sizeof(char));


	// LOOP
	statusloop();
	
	// CLOSE STUFF
	XCloseDisplay(dpy);
	free(output);

	// BY MF
	return 0;
}
