CXXFLAGS=-std=c++11 -std=gnu++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant

all: mapset process_numbers
mapset: mapset.cpp
	g++ -ggdb $(CXXFLAGS) mapset.cpp -o mapset

process_numbers: process_numbers.cpp
	g++ -ggdb $(CXXFLAGS) process_numbers.cpp -o nums

