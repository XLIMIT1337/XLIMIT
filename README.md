sudo apt-get install g++

g++ -o XLIMIT XLIMIT.cpp -static -lpthread -std=c++17 -I. -m32

md5sum XLIMIT > XLIMIT.md5

md5sum -c XLIMIT.md5
