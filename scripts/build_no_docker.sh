#!/bin/bash
apt-get install --no-install-recommends -y libssl-dev zlib1g-dev libsodium-dev libopus-dev

wget wget -O dpp.deb https://dl.dpp.dev/
sudo dpkg -i dpp.deb
rm dpp.deb

mkdir build && cd build
cmake -S ../ -B .
make -j $(nproc)