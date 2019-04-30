PACKAGE_DIR=karuta-pkg
PACKAGE_ARCHIVE=karuta-pkg.tar.gz

setup	:
	python setup.py
	systemctl --user daemon-reload
	systemctl --user enable karuta.socket
	systemctl --user start karuta.socket

package	:
	echo making package
	mkdir -p $(PACKAGE_DIR)
	cp Makefile setup.py wrapper.py karuta.py $(PACKAGE_DIR)
	cp karuta-bin default-isynth.karuta $(PACKAGE_DIR)
	tar cvzf $(PACKAGE_ARCHIVE) $(PACKAGE_DIR)

clean	:
	rm karuta.socket
	rm karuta@.service

uninstall	:
	systemctl --user disable karuta.socket
	rm -f $(HOME)/.local/share/systemd/user/karuta@.service
	rm -f $(HOME)/.local/share/systemd/user/karuta.socket

copy	:
	rm -f karuta-bin default-isynth.karuta
	ln -s ../../karuta-bin .
	ln -s ../default-isynth.karuta .

reload	:
	systemctl --user daemon-reload
