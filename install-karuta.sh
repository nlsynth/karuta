# Minimum script to install Karuta.
# This assumes your are with conventional Python3 environment.

# $ curl -o install-karuta.sh https://raw.githubusercontent.com/nlsynth/karuta/master/install-karuta.sh
# $ sh install-karuta.sh

pip3 install gyp-next
git clone --recursive https://github.com/nlsynth/karuta.git
cd karuta
./configure --prefix=$HOME/.local
make
make install
