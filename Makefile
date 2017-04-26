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
	/bin/bash ./ylwrap src/fe/parser.ypp y.tab.c src/fe/libparse_la-parser.cpp y.tab.h src/fe/libparse_la-parser.hpp y.output src/fe/libparse_la-parser.output -- bison -y -d -g -p z_yy

src/fe/libparse_la-parser.cpp: src/fe/parser.ypp

clean:
	rm -rf src/out/
	rm -f nli-bin
