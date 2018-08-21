# Matrix
A stand-alone calculator for inverses, adjoints & solution to a given set of linear equations.

## Requirements
For the moment **Matrix** doesn't reaquire anything other than the compiler.

You can use any C++ compiler (like Microsoft Visual C++). However, this project was compiled using the GNU Compiler Collection (`g++`).

## How to execute
First of all you need a C++ compiler to compile the program. If you're using the GNU Compiler Collection, you can do this by the following command.
```sh
$ g++ -o play matrix.cpp playground.cpp
```

Once the compilation is done, you can execute the program by
```sh
$ ./play
```

If you are on Windows and willing to use the GNU Compiler Collection for the compilation, here's an [article](http://www1.cmc.edu/pages/faculty/alee/g++/g++.html) that explains how to install it on Windows.

## Implementation
Anyone willing to implement the core workings of this program you might want to play around or extend the class Matrix in the file `matrix.cpp` and corresponding header file `matrix.h`. `playground.cpp` contains a console UI which I'm not really a fan of, despite writing it myself. But the computational methods in that file may be useful.

## Special Thanks to
[James Schloss](https://github.com/leios) for [The Arcane Algorithm Archive](https://www.algorithm-archive.org) project.
