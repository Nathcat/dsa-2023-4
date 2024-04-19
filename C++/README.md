# Data Structures and Algorithms
*University of Sussex 2023 - 2024 ~ [Dr Alessio Santamaria](https://profiles.sussex.ac.uk/p580064-alessio-santamaria)*

Credit for the tasks in these lab classes goes to [Bertie Wheen](https://github.com/bertie-wheen/). This is a fork of the [original repository](https://github.com/bertie-wheen/dsa-2023-4), so the Python version of the tasks and a description of the purpose of these labs can be found in the root directory of this repository.

C++ implementation by [Nathan Baines](https://nathcat.net).

## Why have I done this?
Well, personally I'm not the biggest fan of Python as a language, and given that I am already quite familiar with it I figured that it might be a better use of my time to do these labs in C++ instead.

It wasn't long until I began to curse myself for choosing such a masochistic challenge, as I drowned in Segmentation faults as a result of my lack of experience in the language. But over the labs I gained more and more experience in the memory management system, and my code improved substantially.

# Structure
In this repo you will find directories for each lab, named `Lab#`, and a directory called `Testing`.

The `Testing` directory contains the code for a _**very**_ simple testing framework I wrote for this project.

In the lab directories you will find two sub-directories:

- `LabX`
    - `include` Contains the header files which define the data structures / algorithms implemented in the lab.
    - `src` Contains the source code for testing the implementations in the lab.

# Compiling
This project uses minimum CMake version `3.11.2`.

I have only tested the project using _MinGW Makeiles_ build system on Windows, and _Unix Makefiles_ build system on Linux. See below for instructions to compile on both these platorms.

## Windows (MinGW makefiles)
Enter the following commands _from the C++ directory_.

```
$ cmake . -G "MinGW Makefiles"
$ mingw32-make
```

## Linux (Unix makefiles)
```
$ cmake . -G "Unix Makefiles"
$ make
```

# Using the project
You can run the tests for each lab using the following command on linux, replacing the # with the lab number.

```
./Lab#/build/DSALab#
```

and on Windows:

```
./Lab#/build/DSALab#.exe
```

or

```
start ./Lab#/build/DSALab#.exe
```

although this closes the window once the program has completed.

## Library
This project also includes a shared library which includes all of the implementations of the labs within it, at the path `C++/build/libDSALabs-2024.so` on linux, and `C++/libDSALabs-2024.dll` on windows.