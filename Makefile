include config.mk

prefix ?= /usr/local

nli-bin	: src/out/Default/nli build
	rm -f nli-bin
	ln -s src/out/Default/nli ./nli-bin

src/out/Default/nli: src/Makefile src/fe/libparse_la-parser.cpp config.mk
	make -C src

build:
	make -C src

src/Makefile: src/nli.gyp
	gyp src/nli.gyp --depth=. -f make --generator-output=src

src/fe/libparse_la-parser.cpp: src/fe/parser.ypp
	python ./genparser.py

clean:
	rm -rf src/out/
	rm -f nli-bin
