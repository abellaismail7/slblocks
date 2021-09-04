#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "components.h"
#include "components/coutil.h"

/* Function template
 * const char* [fn_name]([void if not clickable or int clicked]){
 *		[your function implementation]
 *		return [string]
 * }
 *
 */



char* sh_menu(int clicked){
	if(clicked){
		system("menu ui &");
		return NULL;
	}
	return shell("menu");	
}

char* sh_vol(int clicked){
	if(clicked){
		system("volume ui &");
		return NULL;
	}
	return shell("volume");	
}

char* sh_keymap(int clicked){
	if(clicked){
		system("keytoggle ui &");
		return NULL;
	}
	return shell("keytoggle");	
}

// https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-power
const char * battery(void){
	int state = battery_state("BAT0");
	char* icon;
	switch(state){
		case 'F': icon = ""; break; //Full
		case 'C': icon = ""; break; // Charging
		case 'N': icon = ""; break; // Not charging
		case 'D': icon = ""; break; // Discharging
		case 'U': icon = ""; break; // Unkown

		default : icon = "??"; // This should never be triggered

	}
	int perc =  battery_perc("BAT0");

	// this depends on your manufactor
	perc = ((double)perc / 74) * 100; // to have more battery lifespan manufacter charges only 75% 
	return mix("%s %d%%", icon, perc);
}




const char* cpu_usage(void){
	double perc = cpu_perc();
	if(perc == 0) return "st";
	return mix("%s %.1f","ﮧ",perc);
}

const char* mdatetime(void){
	return datetime(" %a %b %d %H:%M");
}

const char* disk_usage(void){
	double used = disk_used("/");
	int prefix = 1024;
	v_human(&used,&prefix);
	return mix("%s %.1lf %ci","﫭", used,prefix);
}

const char* mhostname(void){
	return hostname();
}


const char* mkernel_rel(void){
	return kernel_release();
}

const char * free_mem(void){
	double used = (double) ram_used();
	int prefix = 1024;
	v_human(&used,&prefix);
	return mix("%s %0.1f %ci","",used,prefix);
}


const char* wifi_signal(void){
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


