all:
	g++ -mavx source/main.cpp source/hash.cpp source/test.cpp source/list.cpp source/in.cpp -o hash.exe