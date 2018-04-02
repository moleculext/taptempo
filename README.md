Tap Tempo
=========

A command line tap tempo. Hit enter key with style and you'll get the corresponding number of beats per minute (bpm).

This tool is very useful to quickly find the tempo of a song without launching a big digital workstation like Ardour or LMMS.

Website: https://taptempo.tuxfamily.org

Sources: https://git.tuxfamily.org/taptempo/taptempo.git

Debian Packaging: https://git.tuxfamily.org/taptempo/taptempo_deb_packaging.git

## Demo

Just type "taptempo" in a terminal and hit the enter key while your hearing a song to print the tempo:

```
> taptempo
Hit enter key for each beat (q to quit).

[Hit enter key one more time to start bpm computation...]
Tempo: 143 bpm	
Tempo: 145 bpm	
Tempo: 143 bpm	
Tempo: 143 bpm	
Tempo: 144 bpm	
Tempo: 145 bpm	
Tempo: 146 bpm	q
Bye Bye!

```

## Dowload

Check the [download server](https://download.tuxfamily.org/taptempo) for latest release.

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

To generate debian package, check out the [packaging repo](https://git.tuxfamily.org/taptempo/taptempo_deb_packaging.git) and type:

```debuild -b -us -uc```


### Windows

Install [MSYS2](http://www.msys2.org/) and run `msys/msys2_build.sh` script inside MSYS2 shell.

## Author

François Mazen (francois@mzf.fr)

## Misc

TapTempo is written in C++, but lots of porting in other languages have been developed via the [LinuxFr website](https://linuxfr.org/tags/taptempo/public).


