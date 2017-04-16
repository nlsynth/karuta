import sys
sys.path.append("iroha/")

import iroha_files

EXTRA = ["README.md", "NEWS", "configure.gyp", "Makefile.gyp", "config.mk", "lib/nli", "src/nli.gyp", "iroha/src/iroha.gyp", "src/fe/parser.ypp", "ylwrap", "nli_files.py", "lib/default-isynth.h"]

ifiles = iroha_files.GetGypFileList("iroha/src/iroha.gyp")
iextras = iroha_files.GetExtraFileList("iroha/")
nfiles = iroha_files.GetGypFileList("src/nli.gyp")

files = nfiles + EXTRA + ifiles + iextras

iroha_files.MakeTarBall("nli-tmp", files)
