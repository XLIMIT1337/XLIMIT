sudo apt-get install gcc-multilib g++-multilib

g++ -m32 -o XLIMIT XLIMIT.cpp -static -std=c++17 -I.

file XLIMIT

md5sum XLIMIT > XLIMIT.md5

md5sum -c XLIMIT.md5
