/*	GNU General Public Licence

	This small C program loads the LibOpenBUGS.so ELF shared library and calls the 
	CLI function. Save it as a .c file and then compile it on Linux using 
	
				gcc -o bugs OpenBUGS.c -ldl 
	
	This code should work on a Windows machine if brugs.so is repaced by LibOpenBUGS.dll
	
	A ascii version of this file is in Developer/OpenBUGS.c

*/

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv)
{
	void * handle;
    void (*cli)(void);
 
    handle = dlopen("./LibOpenBUGS.so", RTLD_LAZY);
    if (!handle)
      return 1;
 
    * (void **) (&cli) = dlsym(handle, "CLI");
    (*cli)();
    dlclose(handle);
 
    return 0;
	
}


/*

	As an alternative to using dlopen to load the OpenBUGS library Nathan Coulter has 
	developed the following short C program. Compile it on Linux using 
	
					gcc -o bin/OpenBUGS -L ./lib -Wl,-rpath,\$ORIGIN/../lib src/OpenBUGSCli.c -l OpenBUGS
	
	#include <OpenBUGS.h>

	int main ()
	{
		CLI();
	}

*/


/*

	This is equivalent to the component Pascal program
	
	MODULE BugsClassic;

		IMPORT BugsBRugs;

	BEGIN
		BugsBRugs.CLI
	END BugsClassic.
	
	(*	DevLinker.Link  dos classicbugs.exe := BugsClassic$ 1 Bugslogo.ico 	*)
	
'/

















