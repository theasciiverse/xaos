# XaoS in the terminal

[XaoS](https://github.com/xaos-project/XaoS) is a real-time fractal zoomer:
hold a mouse button and fly into the Mandelbrot set, smoothly and without
waiting for each picture to be drawn. This is XaoS 3.7 with its text-mode
driver, which draws in ASCII art through AAlib, for the
[Asciiverse](https://github.com/theasciiverse) catalog.

XaoS is by Jan Hubicka, Thomas Marsh and the XaoS contributors (see
CREDITS.md), first released in 1996. AAlib is by Jan Hubicka, Kamil Toman
and others. What changed here, and why, is in PATCHES.md; upstream's own
README is README.upstream.md.

## Playing

- **Left button**: hold to zoom in towards the pointer; drag to steer.
- **Right button**: hold to zoom out. **Middle button** (or both): drag to
  move.
- **Arrow keys**: up and down change the zoom speed, left and right the
  number of iterations.
- **a**: autopilot. **Enter**: the menu bar. **h**: help. **u**: undo.
- **m**: from the Mandelbrot set to the Julia set under the pointer, and
  back. **1** to **0**: the first ten fractal types (the rest are in the
  Fractal menu).
- **c** and **f**: outside and inside colouring. **p**: a random palette.
  **y**: colour cycling (left and right set its speed).
- **e**: filters. **q**: quit.

The Help menu has animated tutorials: an introduction to fractals, the
fractal types, XaoS's features, and more, several in other languages too.

## Building

```sh
docker run --rm -v "$PWD":/src -w /src alpine:3.22 sh asciiverse/build.sh   # Linux, static
CC_ARCH=arm64 sh asciiverse/build.sh                                       # macOS
sh asciiverse/stage.sh                                                     # the archive, in stage/
```

## Licence

GPL-3.0-or-later as built (XaoS is GPL-2.0-or-later, see COPYING; it is
linked with AAlib, LGPL-2.0-or-later, see aalib/COPYING, and GSL,
GPL-3.0-or-later).
