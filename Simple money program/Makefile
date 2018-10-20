CXXFLAGS=-std=c++11 -Wpedantic -Wall -Wextra -Werror -Weffc++ -Wzero-as-null-pointer-constant
CFLAGS=-std=c99 -pedantic -Wall -Wextra -Werror -ansi -Wwrite-strings

all: simple_main coins_main coins_menu
simple_main: simple_main.cpp Coins.h
	g++ simple_main.cpp -o simple_main
coins_main: coins_main.cpp Coins.h
	g++ coins_main.cpp -o coins_main 
coins_menu: coins_menu.cpp Coins.h
	g++ coins_menu.cpp -o coins_menu

test:
	create_script simple_main.cpp simple_main
	create_script coins_main.cpp coins_main
	create_script coins_menu.cpp coins_menu
