# SeminarModernCpp

My own code and the LaTeX papers contents of the seminar "Modernes C++" at the University of Stuttgart.
The topic of the paper is Ranges and Views.

## Table of Contents

- [Benchmark Executables: Iterators vs Ranges](./src): Used `cmake` to setup
- [The Article](./paper_template_student)
- [range-adapter-mathe-zusammenfassung.tex](./range-adapter-mathe-zusammenfassung.tex): Mathematical style ranges API summary I had to remove from the paper
- [generator_fib.cpp](./generator_fib.cpp) [generator_fib.js](./generator_fib.js): Little experiments with generators (to be implemented into C++ compilers...)
- [ranges_lazy.cpp](./ranges_lazy.cpp): The implementation of the visual views pipeline example from the paper
- `flake.*`: For reproducibility and swag

## Getting Started

### Dependencies

When you're one of the enlightened Nix-users out there, you just have to `nix-develop` and sacrifice your bandwidth for me (see [flake.nix](./flake.nix)) :^)

If the reader isn't interest in cool tech, the authors made use of the following software:

```shell
# LaTeX
TeX Live 2023/nixos.org
XeTeX 3.141592653-2.6-0.999995
kpathsea version 6.3.5
# C++
## Building
cmake: 3.27.8
(ninja: 1.11.1)
clang: 17.0.6
GCC: 13.2.0
## Dependencies
curl: 8.5.0
nlohmann_json: 3.11.3
```

### C++ Benchmarks

```shell
# Building
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-gcc
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-clang
cmake --build ./cmake-build-gcc --target {benchmark-iter,benchmark-ranges}
cmake --build ./cmake-build-clang --target {benchmark-iter,benchmark-ranges}
# Execution
./cmake-build-(clang|gcc)/benchmark-(ranges|iter)
```

### LaTeX

#### Article

```shell
cd paper_template_student && xelatex samplepaper.tex
```

#### Ranges Summary

```shell
xelatex ./range-adapter-mathe-zusammenfassung.tex
```

### Experiments

```shell
node generator_fib.js
```

## Measurements

I took the measurements in full DE idle mode with all non-essential programs killed and two terminals opened.
I executed every binary 5 times with short waiting periods and formatted them using `vim`.

```shell
$ neofetch
          ▗▄▄▄       ▗▄▄▄▄    ▄▄▄▖            jnnk@dnix
          ▜███▙       ▜███▙  ▟███▛            ---------
           ▜███▙       ▜███▙▟███▛             OS: NixOS 23.11.20240124.a77ab16 (Tapir) x86_64
            ▜███▙       ▜██████▛              Host: *
     ▟█████████████████▙ ▜████▛     ▟▙        Kernel: 6.6.13-xanmod1
    ▟███████████████████▙ ▜███▙    ▟██▙       Uptime: 11 hours, 7 mins
           ▄▄▄▄▖           ▜███▙  ▟███▛       Packages: 1743 (nix-system), 6818 (nix-user)
          ▟███▛             ▜██▛ ▟███▛        Shell: zsh 5.9
         ▟███▛               ▜▛ ▟███▛         Resolution: 2560x1440, 3840x2160
▟███████████▛                  ▟██████████▙   DE: GNOME 45.3 (Wayland)
▜██████████▛                  ▟███████████▛   WM: Mutter
      ▟███▛ ▟▙               ▟███▛            WM Theme: Adwaita
     ▟███▛ ▟██▙             ▟███▛             Theme: Adwaita-dark [GTK2/3]
    ▟███▛  ▜███▙           ▝▀▀▀▀              Icons: Tela-dark [GTK2/3]
    ▜██▛    ▜███▙ ▜██████████████████▛        Terminal: gnome-terminal
     ▜▛     ▟████▙ ▜████████████████▛         CPU: 13th Gen Intel i7-13700K (24) @ 5.300GHz
           ▟██████▙       ▜███▙               GPU: Intel Raptor Lake-S GT1 [UHD Graphics 770]
          ▟███▛▜███▙       ▜███▙              Memory: 8084MiB / 31818MiB
         ▟███▛  ▜███▙       ▜███▙
         ▝▀▀▀    ▀▀▀▀▘       ▀▀▀▘

```

The secondary measurements were made on a ASUS ZenBook with AMD Ryzen 5825U on Power and running a similar NixOS setup and setting as above.
