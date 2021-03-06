# Minimum script to install Karuta.
# This assumes your are with conventional python environment.

pip3 install gyp-next
git clone --recursive https://github.com/nlsynth/karuta.git
cd karuta
./configure --prefix=$HOME/.local
make
make install
