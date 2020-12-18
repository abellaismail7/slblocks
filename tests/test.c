#include "test.h"
#include<stdio.h>
#include<string.h>

#define COMPLENGTH sizeof(components)/sizeof(Comp)

int main(int argc,char** argv){
	char* func_name = "*";
	if(argc == 2)
		func_name = argv[1];		

	Comp component;
	for(int i = 0; i < COMPLENGTH;i++){
		if(func_name[0] != '*' || !strcmp(func_name,component.name) ) continue;
		component = components[i];
		printf("%s:\n%s\n\n",component.name,component.func(component.args));

	}




}



