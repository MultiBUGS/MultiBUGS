# MultiBUGS <a href="https://www.multibugs.org"><img src="https://www.multibugs.org/images/logo.svg" align="right" width = 130></a>

[MultiBUGS](https://www.multibugs.org) implements a simple, automatic algorithm for parallelising Markov chain Monte Carlo (MCMC) algorithms for posterior inference of Bayesian hierarchical models. It builds on the existing algorithms and tools in [OpenBUGS](http://www.openbugs.net/), and so is applicable to the broad range of statistical models that can be fitted using BUGS-language software, but automatically parallelises the MCMC algorithm to dramatically speed up computation. This makes modern multi-core computing accessible to applied statisticians, without requiring any experience of parallel programming.

See the [MultiBUGS website](https://www.multibugs.org) for further details.

## Contents

- [Citation](#citation)
- [Installation](#installation)
- [Pre-built unstable binaries](#pre-built-unstable-binaries)
- [Compiling from source](#compiling-from-source)

## Citation

If you use MultiBUGS in your published work, please cite

Goudie, R. J. B., Turner, R. M., De Angelis, D., Thomas, A. (in press) MultiBUGS: A parallel implementation of the BUGS modelling framework for faster Bayesian inference. Journal of Statistical Software. [arXiv:1704.03216](https://arxiv.org/abs/1704.03216)

## Installation

See the main [MultiBUGS website](https://www.multibugs.org) for installation instructions of the current released version.
The current released version of MultiBUGS works only on Windows and requires [Microsoft MPI (MSI-MPI)](https://msdn.microsoft.com/en-us/library/bb524831(v=vs.85).aspx) (>= v8.1).

## Pre-built unstable development versions

[![Build status](https://ci.appveyor.com/api/projects/status/9ewgftojuttkn9jg/branch/master?svg=true)](https://ci.appveyor.com/project/MultiBUGS/multibugs/branch/master)

### Windows pre-built unstable binaries

1. Download and install [Microsoft MPI (MS-MPI)](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi#ms-mpi-downloads) (v8.1 or newer)

2. Download the [latest `master` branch build of MultiBUGS](https://ci.appveyor.com/api/projects/MultiBUGS/MultiBUGS/artifacts/MultiBUGS.zip?branch=master). Unzip this to, e.g., `C:\Program Files (x86)\MultiBUGS`.

### Linux pre-built unstable binaries

Pre-built Linux binaries in preparation

## Compiling from source

### Compiling from source on Windows

1. Download and install [Microsoft MPI (MS-MPI)](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi#ms-mpi-downloads). Version 8.1 or newer is required, since MultiBUGS uses `MPI_Comm_spawn`. This framework allows running parallel applications on the Windows platform.

2. Download and install [BlackBox 1.7.1](http://blackboxframework.org/index.php?cID=goto-download-page,en-us) from the BlackBox Framework Center. This is the framework that MultiBUGS is written using.

3. Download the [zip archive](https://github.com/MultiBUGS/MultiBUGS/archive/master.zip) of MultiBUGS. Unzip this to, for example, `C:\`

4. Make a new shortcut to the BlackBox.exe file in the newly-installed BlackBox directory (right-click on BlackBox.exe, choose "Create shortcut"). Add the path to the MultiBUGS directory as the `/USE` argument to the `Target` of the shortcut. For example, if BlackBox  is in `C:\Program Files (x86)\BlackBox Component Builder 1.7\` and MultiBUGS is in `C:\MultiBUGS-master`, then change the `Target` to:

    ```
    mpiexec -n 1 "C:\Program Files (x86)\BlackBox Component Builder 1.7\BlackBox.exe" /USE "C:\MultiBUGS-master"
    ```

    and `Start in` to

    ```
    "C:\MultiBUGS-master"
    ```

    You may want to move the shortcut itself to the Desktop to make it easy to access.

5. Double click the shortcut to open MultiBUGS/BlackBox.

6. Within MultiBUGS/BlackBox open `Make.odc`, which is found in the `Developer` directory in the MultiBUGS directory. Click on the `!` beside `DevCompiler.CompileThis`. This will compile MultiBUGS. The compiler will ask you to confirm the creation of many directories: click OK to confirm all of these in turn. Compiling will take a couple of minutes. Once compiling is finished the status bar should say "ok".

7. Close BlackBox/MultiBUGS and then reopen it to complete installation. Note that the first time you compile a model, BlackBox/MultiBUGS will confirm creation of a couple of extra directories. The Windows Firewall may also require you to give BlackBox/MultiBUGS permission: this is needed to allow communication between cores.

8. The shortcut link version will now work. If you would also like to create a self-contained compiled version of MultiBUGS (that doesn't need the BlackBox install) and/or use the `MultiBUGS.exe` executable, follow the following steps:

   (a) Within MultiBUGS/BlackBox open `Linking.odc`, which is found in the `Developer` directory in the MultiBUGS directory. Click on the first two `!` buttons in the "How to link MultiBUGS" section in turn. This creates `OpenBUGS.exe`, which `MultiBUGS.exe` needs. (More precisely, `MultiBUGS.exe` is just a wrapper around `OpenBUGS.exe` that handles setting up MPI.)

   (b) Next, open up `BugsPackage.odc`, which is within the `Rsrc` folder within the `Bugs` folder in the MultiBUGS directory. This opens up the tool that is used to create the self-contained version of MultiBUGS. The path specifies where MultiBUGS will be installed. The other options specify which files are copied to the self-contained installation. Before clicking `ok` to create the self-contained version it is useful to open the Log window (`Info` menu > `Open log`) to make it easy to monitor progress.

   (c) Once this process is complete, `MultiBUGS.exe` within the self-contained version should work, and the BlackBox installation is not required. Note that the first time you compile a model, MultiBUGS will confirm creation of a couple of extra directories. 

### Compiling from source on Linux

On Debian/Ubuntu-based systems

1. Install [BlackBox Cross-Platform](https://blackbox.obertone.ru/download).

2. Install 32-bit [MPICH](https://www.mpich.org)

    ```
    sudo apt install mpich:i386
    ```

3. Download the current `master` branch and open BlackBox (`bbcb`).

    ```
    wget https://github.com/MultiBUGS/MultiBUGS/archive/master.tar.gz
    tar -xzf master.tar.gz
    cd MultiBUGS-master
    bbcb
    ```

4. Open `MPIliblinux.odc` within `Mod` within `System`. Edit the name of the shared object to match that on your install of libmpich. (This will be automated in the future.)

5. Within MultiBUGS/BlackBox open `MakeLinux.odc`, which is found in the `Developer` directory in the MultiBUGS directory. Click on the `!` beside `DevCompiler.CompileThis`. This will compile MultiBUGS. Once compiling is finished the status bar should say "ok".

6. Start up MultiBUGS under MPI

    ```
    mpiexec -n 1 bbcb
    ```
