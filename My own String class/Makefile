all: string_test standard_main
string_test: string_test.cpp String.cpp
	g++ -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant String.cpp string_test.cpp -o string_test
standard_main: standard_main.cpp String.cpp
	g++ -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant String.cpp standard_main.cpp -o standard_main
test:
	create_script string_test.cpp string_test
	create_script standard_main.cpp standard_main

