# MultiBUGS

MultiBUGS implements the simple, generic parallelisation algorithm introduced in Goudie et al (2017). It links together some modules from [OpenBUGS](http://www.openbugs.net/) with a few additional modules to implement our parallelisation algorithm.

## Installation

MultiBUGS currently works only on Windows. (We hope to port it to Linux in the near future.)

1. Download and install [Microsoft MPI (MS-MPI)](https://msdn.microsoft.com/en-us/library/bb524831(v=vs.85).aspx). This framework allows running parallel applications on the Windows platform.

2. Download and install [BlackBox 1.7](http://blackboxframework.org/index.php?cID=goto-download-page,en-us) from the BlackBox Framework Center. This is the framework that MultiBUGS is written using.

3. Download the [zip archive](https://github.com/MultiBUGS/MultiBUGS/archive/master.zip) of MultiBUGS. Unzip this to, for example, `C:\Program Files (x86)\`

4. Make a new shortcut to the BlackBox.exe file in the newly-installed BlackBox directory (right-click on BlackBox.exe, choose "Create shortcut"). Add the path to the MultiBUGS directory as the `/USE` argument to the `Target` of the shortcut. For example, if BlackBox  is in `C:\Program Files (x86)\BlackBox Component Builder 1.7\` and MultiBUGS is in `C:\MultiBUGS-master`, then change the `Target` to:

```
"C:\Program Files (x86)\BlackBox Component Builder 1.7\BlackBox.exe" /USE "C:\MultiBUGS-master"
```

and `Start in` to

```
"C:\MultiBUGS-master"
```

You may want to move the shortcut itself to the Desktop to make it easy to access.

5. Double click the shortcut to open MultiBUGS/BlackBox.

6. Within MultiBUGS/BlackBox open `Make.odc`, which is found in the `Developer` directory in the MultiBUGS directory. Click on the `!` beside `DevCompiler.CompileThis`. This will compile MultiBUGS. The compiler will ask you to confirm the creation of many directories: click OK to confirm all of these in turn. Compiling will take a couple of minutes. Once compiling is finished the status bar should say "ok".

7. Close BlackBox/MultiBUGS and then reopen it to complete installation. Note that the first time you compile a model, BlackBox/MultiBUGS will confirm creation of a couple of extra directories. The Windows Firewall may also require you to give BlackBox/MultiBUGS permission: this is needed to allow communication between cores.
