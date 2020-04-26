### 1. Copy baserom(s) into root folder

Put clean copies of Pokemon Diamond (US) nds rom at `./baserom.nds`, `./arm9/baserom.nds`, and `./arm7/baserom.nds`. All three copies are required and must be identical.

### 2. Install MWCC compiler

The build system requires the use of the Metrowerk C Compiler 2.0/base to compile matching files. We cannot distribute the correct compiler here so join the PRET discord and download the pinned mwccarm.zip zip in #pokediamond and extract it to tools/. Run each of the executables so they ask for a license.dat and provide the one in the rar (it may also ask for it when compiling). This only needs to be done once.

In the future, a GCC option will be available so MWCC is not required to build, however it is required for a matching ROM.

### 3. Dependencies

#### Linux

Building the ROM requires the following packages:

* make
* git
* build-essentials
* binutils-arm-none-eabi
* wine (to run the mwcc executables)

NOTE: If you are using Arch/Manjaro or Void you will only need base-devel instead of build-essentials or make or git. You will still need wine.

Also, if you are using WSL on Windows, please pass NOWINE=1 when compiling, and wine is not necessary for a WSL environment.

#### Windows

Before following the respective guides, please install devkitARM and ensure the DEVKITPRO and DEVKITARM variables are added to bashrc such that:

Msys2:
export DEVKITPRO=C:/devkitPro
export DEVKITARM=${DEVKITPRO}/devkitARM

Cygwin:
export DEVKITPRO=/cygdrive/c/devkitPro
export DEVKITARM=${DEVKITPRO}/devkitARM

You will still require the following packages:

* make
* git
* build-essentials

Install them using either the Cygwin package manager or using pacman on Msys2.

### 4. Build ROM

Run `make` to build the ROM.

Windows Users:

If you get an error in saving configuration settings when specifying the license file, you need to add a system environment variable called LM_LICENSE_FILE and point it to the license.dat file.
