# XMath

A simplistic (and unoptimized) linear math library to create games or graphical applications
using a really simple framework to help understand the underlaying principles before doing
fancy stuff.

## Compilation

Clone it and run cmake:

```sh
mkdir build
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=DEBUG
cmake --build build
```

There are no extra dependencies aside from C11 compiler and CMake.

## Tests

```sh
ninja -c build test
```

## Usage

Link the library (dynamic or static) with your project

```c
#include <xmath.h>

int main() {
    Vec3 a = {1.0f, 1.0f, 1.0f};
    Vec3 b = {1.0f, 2.0f, 2.0f};
    Vec3 c = Vec3Add(a, b);
    return 0;
}
```

You can read the documentation in `docs/html/index.html` after building the project.
