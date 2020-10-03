import lib_files
import test_files
import iroha_files
import sys
sys.path.append("iroha/")
sys.path.append("tests/")
sys.path.append("lib/")

VERSION = "0.6.1"

EXTRA = ["README.md", "NEWS", "configure", "Makefile", "config.mk", "karuta", "src/karuta.gyp", "iroha/src/iroha.gyp",
         "src/fe/parser.ypp", "genparser.py", "karuta_files.py", "examples/top.karuta", "examples/fp16r.karuta"]

DOCS = ["docs/index.rst", "docs/introduction.rst", "docs/reference.rst",
        "docs/usersguide.rst", "docs/designandimpl.rst", "docs/experimental.rst"]

ifiles = iroha_files.GetGypFileList("iroha/src/iroha.gyp")
iextras = iroha_files.GetExtraFileList("iroha/")
kfiles = iroha_files.GetGypFileList("src/karuta.gyp")

tfiles = test_files.GetFiles("tests/")
lfiles = lib_files.GetFiles("lib/")

files = kfiles + DOCS + EXTRA + lfiles + ifiles + iextras + tfiles

iroha_files.MakeTarBall("karuta-" + VERSION, files)
