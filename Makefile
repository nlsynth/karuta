include config.mk

prefix ?= /usr/local

karuta-bin	: src/out/Default/karuta build
	rm -f karuta-bin
	ln -s src/out/Default/karuta ./karuta-bin

src/out/Default/karuta: src/Makefile src/fe/parser.cpp config.mk
	make -C src

.PHONY: build
build:
	make -C src

src/Makefile: src/karuta.gyp
	gyp src/karuta.gyp --depth=. -f make --generator-output=src

src/fe/parser.cpp: src/fe/parser.ypp
	python ./genparser.py

.PHONY: clean
clean:
	rm -rf src/out/
	rm -f karuta-bin

.PHONY: install
install:
	install -D lib/karuta $(prefix)/bin/karuta
	install -D karuta-bin $(prefix)/bin/karuta-bin
	install -D lib/default-isynth.karuta $(prefix)/share/karuta/default-isynth.karuta
	install -D lib/karuta_exit.v $(prefix)/share/karuta/karuta_exit.v
	install -D lib/karuta_wait.v $(prefix)/share/karuta/karuta_wait.v
	install -D lib/fp/fp16r.karuta $(prefix)/share/karuta/fp/fp16r.karuta
	install -D lib/fp/fp16rmul.v $(prefix)/share/karuta/fp/fp16rmul.v
	install -D lib/fp/fp16raddsub.v $(prefix)/share/karuta/fp/fp16raddsub.v
	make -C iroha install-data

.PHONY: pkg
pkg:
	mkdir pkg
	cp karuta pkg/
	cp karuta-bin pkg/
	mkdir pkg/lib
	cp lib/default-isynth.karuta pkg/lib
	cp lib/karuta_exit.v pkg/lib
	cp lib/karuta_wait.v pkg/lib
	cp lib/fp/fp16r.karuta pkg/lib
	cp lib/fp/fp16rmul.v pkg/lib
	cp lib/fp/fp16raddsub.v pkg/lib
	tar cvzf pkg.tar.gz pkg
	rm -rf pkg
