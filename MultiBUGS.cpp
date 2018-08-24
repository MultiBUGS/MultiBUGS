#include <windows.h>
#include <string>
#include <shellapi.h>
#include <shlobj.h>
#include <iostream>

// MultiBUGS.exe is a very simple wrapper to avoid users needing to call
// mpiexec themselves.
//
// The program essentially just (syncronously) calls
//
// mpiexec -n 1 <OtherArgs> OpenBUGS.exe <OpenBUGSArgs>
//
// where <OpenBUGSArgs> are the usual BUGS/BlackBox arguments
// and <OtherArgs> are any other arguments, which are passed to mpiexec
//
//
// Should be compiled with VS using
// rc -fo Win/Rsrc/Bugslogo.res Win/Rsrc/Bugslogo.rc
// cvtres -machine:ix86 -out:Bugslogo.obj Win/Rsrc/Bugslogo.res
// cl /EHsc MultiBUGS.cpp /link shell32.lib Bugslogo.obj /subsystem:windows /entry:mainCRTStartup

// Returns path to directory containing this executable
std::string ExePath() {
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  std::string::size_type pos = std::string(buffer).find_last_of("\\/");
  return std::string(buffer).substr(0, pos);
}

int main(int argc, char *argv[]){
  // split args into those for mpiexec and those for BlackBox/MultiBUGS
  std::string mpiexec_args, multibugs_args;
  int i = 1; // ignore exe name
  while (i < argc){
    if (// First handle two-part BlackBox/MultiBUGS arguments
        strcmp("/PAR", argv[i]) == 0 ||
        strcmp("/USE", argv[i]) == 0 ||
        strcmp("/INIFILE", argv[i]) == 0 ||
        strcmp("/O", argv[i]) == 0 ||
        strcmp("/P", argv[i]) == 0 ||
        strcmp("/LOAD", argv[i]) == 0 ||
        strcmp("/LRTB", argv[i]) == 0 ||
        strcmp("/LANG", argv[i]) == 0){
      multibugs_args = multibugs_args + " " + argv[i];
      if (i + 1 < argc){
        multibugs_args = multibugs_args + " " + argv[i + 1];
      }
      i = i + 2;
    } else if (// Now handle BlackBox/MultiBUGS flags
               strcmp("/HEADLESS", argv[i]) == 0 ||
               strcmp("/PORTABLE", argv[i]) == 0 ||
               strcmp("/EMBEDDING", argv[i]) == 0 ||
               strcmp("/NOAPPWIN", argv[i]) == 0 ||
               strcmp("/NOSCROLL", argv[i]) == 0 ||
               strcmp("/FULLSIZE", argv[i]) == 0){
      multibugs_args = multibugs_args + " " + argv[i];
      i++;
    } else {// Now handle any other arguments/flags
      mpiexec_args = mpiexec_args + " " + argv[i];
      i++;
    }
  }

  // build full call to mpiexec
  std::string param =
    " -n 1" +
    mpiexec_args +
    " \"" +
    ExePath() +
    "/OpenBUGS.exe\"" +
    multibugs_args;

  // call mpiexec
  SHELLEXECUTEINFO ShExecInfo = {0};
  ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  ShExecInfo.hwnd = NULL;
  ShExecInfo.lpVerb = "open";
  ShExecInfo.lpFile = "mpiexec";
  ShExecInfo.lpParameters = param.c_str();
  ShExecInfo.lpDirectory = NULL;
  ShExecInfo.nShow = SW_HIDE;
  ShExecInfo.hInstApp = NULL;
  ShellExecuteEx(&ShExecInfo);

  // wait till mpiexec is finished
  WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
  CloseHandle(ShExecInfo.hProcess);
}
