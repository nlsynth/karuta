# WIP makefile using gyp. This will replace autotools based makefile.
#
nli-bin	: all
	ln -s src/out/Default/nli ./nli-bin

all	: src/Makefile
	make -C src

src/Makefile: makefile
	gyp src/nli.gyp --depth=. -f make --generator-output=src

clean:
	rm -rf src/out/
	rm -f nli-bin
