sudo apt-get install gcc-multilib g++-multilib

g++ -o XLIMIT XLIMIT.cpp -static -lpthread -std=c++17 -I. -m32

file XLIMIT

md5sum XLIMIT > XLIMIT.md5

md5sum -c XLIMIT.md5
