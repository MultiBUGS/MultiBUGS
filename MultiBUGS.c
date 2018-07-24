#include <windows.h>
#include <ShellAPI.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This should be compiled with VS using
// cl /EHsc MultiBUGS.c /link shell32.lib /subsystem:windows /entry:mainCRTStartup

int main(int argc, char **argv) {
    unsigned int i;
    size_t len = 0;
    char *all_args;

    char *cmd = "/C mpiexec -n 1 OpenBUGS.exe /LOAD BugsMulti";
    len = strlen(cmd);

    for(i=1; i<argc; i++) {
        len += strlen(argv[i]);
    }

    all_args = (char *)malloc(len+argc-1);
    memcpy(all_args, cmd, strlen(cmd));

    for(i=1; i<argc; i++) {
        memcpy(all_args, argv[i], strlen(argv[i]));
        all_args += strlen(argv[i])+1;
        *(all_args-1) = ' ';
    }
    *(all_args-1) = 0;

   ShellExecute(0, "open", "cmd.exe", all_args, NULL, SW_HIDE);
   return 0;
}