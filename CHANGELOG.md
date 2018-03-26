TapTempo Changelog
==================

## 1.3.0 - 2018-03-26

- When input arguments are negative, the value is set to default value instead of max value.
- When two hits are at same timestamp, infinity is displayed.
- Replace STRINGIFY by CMake variables in taptempo_config.h.in

## 1.2.1 - 2018-03-18

- Force C++11 in CMake file to fix build error.

## 1.2.0 - 2018-01-29

- Change display decimal precision to 0 digit.
- Add command line arguments to change reset time, sample count and precision.
- Add help message and version.
- Update man page.

## 1.1.2 - 2017-10-24

- Add debian package files.

## 1.1.1 - 2017-10-19

- Script to build for Windows in MSYS2.

## 1.1.0 - 2017-10-17

- Reset bpm computation when no entry in 5 seconds.
- Improve CMakeLists.txt with install and gettext/Intl.

## 1.0.0 - 2017-10-15

- Initial release, `GPL-3.0+`.
