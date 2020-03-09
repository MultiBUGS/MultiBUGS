#include <string>
#include <cstring>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#endif

#ifdef __linux__
#include <cstdlib>
#include <libgen.h>
#include <unistd.h>
#include <limits.h>
#endif

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
std::string ExePath(){
#ifdef _WIN32
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  std::string::size_type pos = std::string(buffer).find_last_of("\\/");
  return std::string(buffer).substr(0, pos);
#endif
#ifdef __linux__
  char buff[PATH_MAX];
  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
    return std::string(dirname(buff));
  }
#endif
}

int main(int argc, char *argv[]){

  // Insanely, you need to triple quote on Windows to pass through the
  // quotes - see
  // https://docs.microsoft.com/en-us/windows/win32/api/shellapi/ns-shellapi-shellexecuteinfoa
  // #ifdef _WIN32
  std::string quote = "\"";
  // #endif
  // #ifdef __linux__
  //   std::string quote = "\"";
  // #endif

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
      if (i + 1 <= argc){
        if (std::string(argv[i + 1]).find(" ") != std::string::npos){
          multibugs_args = multibugs_args + " " + quote + argv[i + 1] + quote;
        } else {
          multibugs_args = multibugs_args + " " + argv[i + 1];
        }
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
      if (std::string(argv[i]).find(" ") != std::string::npos){
        mpiexec_args = mpiexec_args + " " + quote + argv[i] + quote;
      } else {
        mpiexec_args = mpiexec_args + " " + argv[i];
      }
      i++;
    }
  }

#ifdef _WIN32
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
#endif

#ifdef __linux__
  // build full call to mpiexec
  std::string param =
    "mpiexec -n 1" +
    mpiexec_args +
    " \"" +
    ExePath() +
    "/OpenBUGS\"" +
    multibugs_args;
  std::cout << param;
  //  std::system(param.c_str());
#endif
}
