# Collett

A C++ version of [novelWriter](https://github.com/vkbo/novelWriter).

This project is just to test out how much work it would be to rewrite the Python application in C++
using the same QtWidget based structure.

## Qt6 Libraries

Either build Qt6 from source, or download the source backages from the
[Qt Open Source](https://www.qt.io/download-open-source) page.

For the Collett build to find the Qt6 libraries, either specify the path via `-DCMAKE_PREFIX_PATH`
to the `cmake` command, or make a symlink from the binary folder to `lib/qt6` inside the source.
