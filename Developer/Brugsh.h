/*
	OpenBUGS header file 
	GNU General Public Licence

	Thanks to Nathan Coulter for help with writing this file
	
	An ascii version of this file is in Developer/OpenBUGS.h
	
*/

extern void CLI ();
extern void BugsCmd(char **command, int *len);
extern void CharArray (char **procedure, int *len, char **x, int *lenX, int *res);
extern void CmdInterpreter (char **command, int *len, int *res);
extern void Guard (char **procedure, int *len, int *x, int *res);
extern void Integer (char **procedure, int *len, int *x, int *res);
extern void IntegerArray (char **procedure, int *len, int *x, int *lenX, int *res);
extern void Real (char **procedure, int *len, double *x, double *y, int *res);
extern void RealArray (char **procedure, int *len, double *x, int *lenX, int *res);
extern void SetWorkingDir (char **path, int *len);
extern void SetTempDir(char **path, int *len);
extern void UseBufferFile ();
extern void UseConsole ();
