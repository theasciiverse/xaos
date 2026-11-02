#!/bin/sh
# Lays out the av archive in stage/: the start script at the top, XaoS in
# lib/ with the data it looks for beside itself (help/, tutorial/,
# catalogs/ and examples/, the examples in one folder as upstream's
# `make install` puts them).
set -eu
rm -rf stage && mkdir -p stage/lib/help stage/lib/tutorial stage/lib/catalogs stage/lib/examples
cp asciiverse/xaos stage/xaos
cp xaos stage/lib/xaos
cp help/xaos.hlp stage/lib/help/
cp tutorial/*.xaf tutorial/*.xhf stage/lib/tutorial/
cp catalogs/*.cat stage/lib/catalogs/
cp examples/*/*.xaf examples/*/*.xpf examples/README stage/lib/examples/
cp COPYING README.md PATCHES.md stage/
cp aalib/COPYING stage/COPYING.AAlib
