include config.mk

prefix ?= /usr/local

nli-bin	: src/out/Default/nli build
	rm -f nli-bin
	ln -s src/out/Default/nli ./nli-bin

src/out/Default/nli: src/Makefile src/fe/parser.cpp config.mk
	make -C src

.PHONY: build
build:
	make -C src

src/Makefile: src/nli.gyp
	gyp src/nli.gyp --depth=. -f make --generator-output=src

src/fe/parser.cpp: src/fe/parser.ypp
	python ./genparser.py

.PHONY: clean
clean:
	rm -rf src/out/
	rm -f nli-bin

.PHONY: install
install:
	install -D lib/nli $(prefix)/bin/nli
	install -D nli-bin $(prefix)/bin/nli-bin
	install -D lib/default-isynth.n  $(prefix)/share/nli/default-isynth.n
