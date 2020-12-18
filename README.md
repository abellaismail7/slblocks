# slblocks - Suckless statusbar
slslblocks is a suckless status monitor for dwm. created by C Noob using existing code

# Still sucks
this a very first version of this programm which means its sucks but I hopeit will be better.

# slstatus + dwmblocks
we try to merge the power of dwmblocks with performance of slstaus togther

- [dwmblocks](https://github.com/torrinfail/dwmblocks/blob/master/README.md): is clickable but uses a lot of shell commands.
- [slstatus](https://github.com/drkhsh/slstatus): is minimal but not clickable.

# Requirements
Currently slstatus works on Linux (OpenBSD & FreeBSD in Future).
In order to build slstatus you need the Xlib header files.

# Installation
```
sudo make install
```

# Configuration
you can uses built-in functions and rearrange them by modifiying config.h file.
Note: Recompile the source code.

## shell function
Note: using shell function for every command has a cost but if you want to do it just use dwmblocks.
```
const char* keyar[] = {"0","keytoggle"};

static const Block blocks[] = {
	/*Func*/			/*ival*/	/*Sig*/	/*Argements*/
	{ shell,			0,            3,	keyar							},
};

```
- func argument: takes built-in function.
- interval arg: execute func every x second if 0 will wait for a signal to update.
- Signal arg: unique value for notifying slblocks to update block or that block is clicked.
- Args arg: some configuration of func.

# AGAIN
this a very early version from a c noob so don't expect anythings

<a href="https://github.com/torrinfail/dwmblocks/blob/master/README.md">dwmblocks</a>
