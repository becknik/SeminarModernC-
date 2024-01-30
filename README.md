# SeminarModernCpp

My own code and the LaTeX papers contents of the seminar "Modernes C++" at the University of Stuttgart.
The topic of the paper is Ranges and Views

## Getting Started

### Dependencies

When you're one of the bespoken Nix-users out there, you just have to `nix-develope` (see [flake.nix](./flake.nix)) :^)

Else, the programs the authors made use of:

```shell
# Building
cmake: 3.27.8
(ninja: 1.11.1)
clang: 17.0.6
GCC: 13.2.0
# Dependencies
curl: 8.5.0
nlohmann_json: 3.11.3
```

### C++ Benchmarks

```shell
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-gcc
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -B ./cmake-build-clang
cmake --build ./cmake-build-gcc --target {benchmark-iter,benchmark-ranges}
cmake --build ./cmake-build-clang --target {benchmark-iter,benchmark-ranges}
# Execution
./cmake-build-(clang|gcc)/benchmark-(ranges|iter)
```

### LaTeX

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
