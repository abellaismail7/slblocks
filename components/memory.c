#include<stdio.h>
#include<string.h>
#include "coutil.h"

int start_with(FILE* fp,char* match,int ps);
long int str_to_long(FILE* fp);
/*** 
 * args[0] = icon
 * ***/
char* free_mem(char** args){
	FILE *fptr;
	fptr = fopen("/proc/meminfo","r");
	if(fptr == NULL){
	  return "error";
	}
	
	char c;
	char* fields[4] ={
		"MemTotal","MemFree","Buffers","Cached"
	};
	int values[4]; 
	
	while(1){
		// loop over fields
		for(int i=0;i < 4;i++){
			long int fps = ftell(fptr);
			short ps = start_with(fptr,fields[i],i); // -1 means no match 0-3 is position of match in fields
			if(ps != -1){
			  values[ps] = str_to_long(fptr);
			  break;
			}
			// if nomatch reset and try
			fseek(fptr,fps,SEEK_SET);
		}
		//next line or end of file
		while( (c = fgetc(fptr)) != EOF && c != '\n');
		if(c == '\n') continue; // next line
		if(c == EOF) break; // break this shit
	}
  	fclose(fptr); // close file
  	double gb= 1024 * 1024;
	sprintf(
			buf,
			" %s %.2f/%.1f",
			args[0],
			(values[0]-values[1]-values[2]-values[3])/gb,
			values[0]/gb);  
  	return buf;
}

int start_with(FILE* fp,char* match,int ps){
	char c;
	do{
	  c = fgetc(fp);
	  if(*match != c) return -1;
	
	}while(*(++match) != '\0');
	
	if(fgetc(fp) != ':') return -1;
	return ps;
}

long int str_to_long(FILE* fp){
	long int total = 0;
	char c;
	while((c = fgetc(fp) ) < 48 || c > 57) ;
	
	do{
	  total *= 10;
	  total += c - 48;
	}while((c = fgetc(fp)) > 47 && c < 58 );
	
	return total;
}
