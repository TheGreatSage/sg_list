# sg_list

List Testing Repository

This is mostly for learning and messing around, It's probably not very good so I would recommend to stay away from this.

Run `make` to run the test

Most of this funtionality is very standard and lots of it is very similar to other open source lists, it really is nothing special.

Usage
---

This is designed to be used as a single header file: `sg_list.h`  
This follows the [stb](https://github.com/nothings/stb) header format, kinda, like this:

```lang-c
#define SG_LIST_IMPLEMENATION
#include "sg_list.h"
```

2 Files
---
Why are there 2 source files if this is designed as a single header library?  

Well this is designed in 2 files, then just merged into one crudly. There are probaly much better ways to do this, but this is mostly just for my personal use so it works. You can include both and it should work or you should be able to define `SG_LIST_IMPLEMENATION` and just need the `sg_list.h`.

Makefile
---
The make file is a modified one from [Raylib](https://github.com/raysan5/raylib). It is probably a little bloated to do a simple test, but I have found it easy to add different configurations using it so I keep versions of it around.

This project has two different `make` commands, a simple `make` will run the `main.c` file running the test. A `main static` will create a library file, the library thing was just me messing around with make, so just ignore that.

Compiling
---
This was written / tested using VSCode using MSYS2 mingw32-make to compile with gcc 11.2.