#include<stdio.h>
#include<string.h>
#include "coutil.h"

FILE *fptr;
long int file_to_long(const char* filename);

int long ch_full = -1;

const char* battery_perc(char**args){
	if(ch_full == -1){
		ch_full = file_to_long("/sys/class/power_supply/BAT0/charge_full");	
	}

	int long ch_now = file_to_long("/sys/class/power_supply/BAT0/charge_now");	
	char* icon;

	fptr = fopen("/sys/class/power_supply/BAT0/status","r");
	if(fptr == NULL){
	  return 0;
	}

	char c = fgetc(fptr);
	fclose(fptr);

	if(c == 'F'){	//Full
		icon = args[1];
	}else if( c == 'C'){ // Charging
		icon = args[2];
	}else if(c == 'N'){ // Not charging
		icon = args[3] ;
	}else if(c == 'D'){ // Discharging
		icon = args[4] ;
	}else if(c == 'U'){ // Unkown
		icon = args[5];
	}else{
		icon = args[5];
	}
	
	int batper =(ch_now * 100)/ch_full;
	int cur = 0;

	while(*icon != '\0'){
		buf[cur++] = *icon;
		icon++;
	}
	buf[cur++] = ' ';	

	int tens = 1000;

	while(tens > batper)
		tens /= 10;
	tens *=10;

	while((tens /= 10)){
		int r = batper / tens;
		buf[cur++] = r + '0';
		batper %= tens;
	}

	buf[cur++] = '%';	
	

	buf[cur++] = '\0';	
  	
	return buf;
}



long int file_to_long(const char* filename){
	fptr = fopen(filename,"r");
	if(fptr == NULL){
	  return 0;
	}

	long int total = 0;
	char c;
	
	while((c = fgetc(fptr)) > 47 && c < 58 ){
	  total *= 10;
	  total += c - 48;
	}
	fclose(fptr);
	return total;
}
