# Changes from upstream

This is the Asciiverse packaging of [XaoS](https://github.com/xaos-project/XaoS),
the real-time fractal zoomer by Jan Hubicka, Thomas Marsh and the XaoS
contributors (CREDITS.md), first released in 1996, built with its text-mode
driver on AAlib so it runs in a terminal. Upstream is the `upstream` remote;
the `asciiverse` branch starts from the tag `release-3.7` (`1709b93`,
2019-05-11), the last release with the AAlib driver: XaoS 4 is Qt only.

`configure.ac` at that tag still says 3.6; the release is 3.7, and this
build says 3.7 (`asciiverse/include/xaos/version.h`).

## AAlib, in aalib/

XaoS's text driver draws with AAlib, the ASCII art library by Jan Hubicka,
Kamil Toman and others, which no system has in a form we can link into one
binary for Linux and macOS. It is in `aalib/`, built up in the usual order:

1. **AAlib 1.4rc5 as released** (2001-04-26), credited to Jan Hubicka, from
   Debian's copy of the tarball: `aalib_1.4p5.orig.tar.gz`, sha256
   `fbddda9230cf6ee2a4f5706b4b11e2190ae45f5eda1f0409dc4f99b35e0a70ee`.
2. **Debian's patches** from aalib 1.4p5-51.1, one commit each under its
   own author (Gergely Nagy, Jonathan Carter, Sven Joachim, Andrey
   Rakhmatullin), tagged `aalib/debian/1.4p5-51.1`. Debian's packaging
   repository is the `aalib-debian` remote.
3. **Ours**, below.

## Code

- **AAlib draws the right way round.** Debian's patch for ncurses' opaque
  `WINDOW` (Debian bug #1057381) calls `getmaxyx(stdscr, *width, *height)`,
  but `getmaxyx` gives the rows first, so the curses driver swapped width
  and height: a 100x30 terminal got 30 columns by 100 rows. Fixed in
  `aalib/src/aacurses.c`. (Debian's own libaa1 has the same bug.)
- **The pointer follows the mouse.** ncurses asks xterm-style terminals
  for presses and releases only, so XaoS saw the pointer only where a
  button went down: a drag did not steer the zoom, fast Julia mode did not
  follow the mouse, and moving to the top row did not open the menu bar.
  AAlib's curses mouse driver also asks for all motion (mode 1003) and
  turns it off on the way out.
- **Arrow keys work.** XaoS treats them as held keys (up and down for the
  zoom speed, left and right for the iterations, or the cycling speed),
  which the aa driver only reported from keyboards that send key
  releases; AAlib's curses keyboard sends none, so in a terminal they did
  nothing. Each press now counts as a press and release, and the
  terminal's key repeat steps on while the key is held.
- **q quits again.** 3.7 removed Quit's key when the Qt driver got its own
  shortcut (`a3223b3`), which left the text driver without one. Reverted:
  q gives Exit now / Not yet, as in 3.6.
- **The built-in help is back.** 3.7 replaced it with a link to the wiki
  (`91c07cb`) and made the help window's buttons run `xdg-open`
  (`e7a7173`). `help/xaos.hlp` is restored from before `91c07cb` and
  `e7a7173` is reverted, so h opens the full help again, with OK, Back and
  Main, and every menu item's help works.
- **User formulas build with current compilers.** 3.7 updated the formula
  parser (sffe), whose function table calls each function with a second
  `payload` argument, but the GSL versions kept one argument; calling them
  through the two-argument pointer is undefined behaviour, and GCC 14
  refuses it. They take (and ignore) the payload now.

## Build

`asciiverse/build.sh` replaces upstream's configure, which looks for a
system AAlib and wants gettext. Everything is built from source into
`av-build/` and linked statically: zlib 1.3.2 and libpng 1.6.59 (saving
images, rendering animations), GSL 2.8 (its complex functions, for user
formulas; tarball checked against its sha256, the GNU signature verified
when it was pinned), AAlib from `aalib/` with only its curses, stdout and
stdin drivers (`asciiverse/include/aalib/config.h`), and XaoS with its
text driver only, from `asciiverse/include/xaos/aconfig.h` in place of
configure's. Linux is static musl (Alpine), needing only terminfo; macOS
uses the system's ncurses.

No gettext: the menus and help are English. The animated tutorials keep
all their languages (`catalogs/`). `<malloc.h>`, which macOS lacks, comes
from a one-line shim in `asciiverse/include/compat/`.

## Licence

XaoS is GPL-2.0-or-later (COPYING), AAlib LGPL-2.0-or-later
(`aalib/COPYING`, shipped as COPYING.AAlib) and GSL GPL-3.0-or-later, so
the binary, which links all three, is GPL-3.0-or-later. zlib, libpng and
ncurses are under their own permissive licences.

## Packaging (new files)

- `asciiverse/build.sh`, `asciiverse/include/`: the build above.
- `asciiverse/xaos`: the start script. XaoS finds its help, tutorials and
  examples beside the binary it was started as, so the script starts it by
  its full path. XaoS saves to the folder it runs in: the one you started
  it from, or your home folder when that is the install folder (av starts
  titles there), so saved files outlive an uninstall.
- `asciiverse/stage.sh`: the archive, with the start script, `lib/xaos`
  and `lib/{help,tutorial,catalogs,examples}` (the examples in one folder,
  as upstream's `make install` does), COPYING, COPYING.AAlib, README.md
  and this file.
- `asciiverse/nfpm.yaml`: .deb, .rpm and Arch packages, everything in
  `/usr/lib/xaos`, the start script in `/usr/bin`; they conflict with the
  distributions' own `xaos` (XaoS 4).
- `.github/workflows/release.yml`: static Linux (x86_64, aarch64) and
  macOS (x86_64, arm64), plus the packages and SHA256SUMS, on our tags
  (`v3.7-av.N`).
- `asciiverse/record-preview.py`, `asciiverse/preview.xaf`,
  `asciiverse/xaos.cast`: the catalog preview, 100x30, about 26 s, XaoS
  playing its own animation script: the whole set, a dive into Elephant
  Valley and back, a Julia set morphing into Douady's rabbit, colour
  cycling. Recorded with hub's castrec and re-encoded at 25 fps by
  `asciiverse/cast-cap-fps.py` (from demos/tarts, plus the REP escape
  ncurses uses).
- `README.md` is ours; upstream's is README.upstream.md.
