#!/usr/bin/env bash

export DEBIAN_FRONTEND=noninteractive

echo 'Installing Make'
apt-get install make
echo 'Installing Valgrind'
sudo apt-get install valgrind
echo 'Installing Cppcheck'
apt-get -y install cppcheck
echo 'Installing Clang-Format'
apt-get install clang-format
