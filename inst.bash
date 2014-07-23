#!/bin/bash 
#
# install Traffic generators Mausezahn


wget http://www.perihel.at/sec/mz/mz-0.40.tar.gz
tar -xvzf mz-0.40.tar.gz
rm -r mz-0.40.tar.gz

sudo apt-get install cmake
sudo apt-get install libpcap0.8-dev
sudo apt-get install libnet1-dev
sudo apt-get install libcli-dev

cd mz-0.40/

cmake .
make 
sudo make install 

echo "l'exécutable est dans le dossier /usr/local/sbin/" 
