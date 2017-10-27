Tap Tempo
=========

A command line tap tempo. Hit enter key with style and you'll get the corresponding number of beats per minute (bpm).

## License

GNU General Public License v3.0 (`GPL-3.0+`, see `LICENSE.txt`).

## Build instructions

### Requirements:
- CMake
- Gettext
- Intl

### Linux

```bash
mkdir _build
cd _build
cmake ..
make
make DESTDIR="/path/to/install" install
./path/to/install/bin/taptempo
```

Generate debian package:

```debuild -b -us -uc```


### Windows

Install [MSYS2](http://www.msys2.org/) and run `msys/msys2_build.sh` script inside MSYS2 shell.

## Author
François Mazen (francois@mzf.fr)

