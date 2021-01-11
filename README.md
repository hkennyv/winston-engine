# winston-engine

## Overview

The winston engine is a 2D gaming engine written in C++ using libsdl named
after my cat, Winston.

**NOTE:** this is not meant to be a production game engine, this project is
still in development and is purely for learning purposes. That being said, any
suggestions/criticisms are welcome :)

## Development

### Dependencies

This project requires the following dependencies:

- sdl2 # core sdl2 library
- sdl2_image # handling images
- sdl2_ttf # handling fontface rendering
- sdl2_mixer # playing sounds
- lua # scripting interface
- glm # mathematics and vector library

The lua and glm dependencies are included in the repository (so you may skip)
installing them through your package manager if you'd like.

#### Installing on Mac OS

```
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer lua glm
```

#### Installing on Debian/Ubuntu

```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libglm-dev
```

#### Installing on Windows

TBD (I haven't had a chance to setup on my Windows PC yet...)

### Buliding and Running

To build the program, simply use:

```
make
```

... or if you'd like to do a debug build:

```
make debug
```

Lastly, to run the program, use:

```
make run
```

## Resources

- [lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
