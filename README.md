# Realm Of Enigmas
> A fork of [@lw-lonewolf/Realm-of-Enigmas](https://github.com/lw-lonewolf/Realm-of-Enigmas/tree/engine-development)
> Made as a university project.

A C++ based graphics top-down platformer game made with SFML.

## How do I try it out?
You can compile the sources manually or run the release executables

### Download releases:
Head to the [releases](releases) page to download a precompiled version of the game.

### Compile from sources
This guide is for compiling on linux, although compiling on Windows is possible but not supported.

The project dependencies can be installed by:
```sh
sudo apt install git make cmake clang libsfml-dev
```
Next, clone the repo, and compile the code.

```sh
git clone https://github.com/thomas-catt/enigma-game.git
cd enigma-game
```

To compile using CMake:
```sh
cmake .
make
```

The executable `window` is placed in `bin`. To run it:
```sh
./bin/window
```

The last two steps can be automatically performed through the install script:
```sh
./run.sh # Compiles and runs the executable
```

# I want to contrinute!
By the time this repository is public, This project would have already been discontinued. Sorry.
