#!/usr/bin/env python3
"""Records the catalog preview at 100x30 with hub/tools/castrec.py: XaoS
plays asciiverse/preview.xaf (the whole set, Elephant Valley, a Julia set
morphing into Douady's rabbit, colour cycling), rendered live by its text
driver, then quits with q. XaoS redraws the whole screen every frame, so
the raw recording is re-encoded at 25 fps (asciiverse/cast-cap-fps.py).
About 26 s.

  asciiverse/record-preview.py ./xaos asciiverse/xaos.cast   (from the repo root)
"""
import os, subprocess, sys, tempfile

here = os.path.dirname(os.path.abspath(__file__))
binary, out = os.path.abspath(sys.argv[1]), os.path.abspath(sys.argv[2])
castrec = os.path.join(here, "../../../hub/tools/castrec.py")
raw = tempfile.mktemp(suffix=".cast")
try:
    # q then 1 (Exit now) after the animation, so the end is a clean exit
    subprocess.run([sys.executable, castrec, raw, os.path.dirname(binary), "w26.2;kq;k1;w0.5",
                    "--", binary, "-play", os.path.join(here, "preview.xaf")], check=True)
    subprocess.run([sys.executable, os.path.join(here, "cast-cap-fps.py"), raw, out, "25"], check=True)
finally:
    if os.path.exists(raw):
        os.remove(raw)
print(out, os.path.getsize(out) // 1024, "KB")
