# SeminarModernCpp

Eigener Code, den ich für das Seminar "Modernes C++" zum Thema C++23 und Ranges &amp; Views erstellt habe

## Getting Started

### Nix

```shell
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-gcc
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-clang
cmake --build ./cmake-build-gcc --target {benchmark-iter,benchmark-ranges}
cmake --build ./cmake-build-clang --target {benchmark-iter,benchmark-ranges}
```
