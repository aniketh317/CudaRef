all: ../datacommon/input_16.in ../datacommon/input_4096.in ../datacommon/input_8192.in ../datacommon/input_16384.in rmm rmmm

rmm: main.cpp header/single_thread.h header/multi_thread.h
	g++ -g -ggdb main.cpp -o rmm -I ./header -lpthread -mavx -mavx2

rmmm: main2.cpp header/single_thread.h header/multi_thread.h
	g++ -g -ggdb main2.cpp -o rmmm -I ./header -lpthread -mavx -mavx2

data/generate: data/generate.cpp
	g++ ./data/generate.cpp -o ./data/generate

../datacommon/input_16.in: data/generate
	./data/generate 16 

../datacommon/input_512.in: data/generate
	./data/generate 512 

../datacommon/input_1024.in: data/generate
	./data/generate 1024 

../datacommon/input_4096.in: data/generate
	./data/generate 4096 

../datacommon/input_8192.in: data/generate
	./data/generate 8192 

../datacommon/input_16384.in: data/generate
	./data/generate 16384 

run: data/input_16.in data/input_4096.in data/input_8192.in data/input_16384.in rmm
	./rmm data/input_16.in
	./rmm data/input_4096.in
	./rmm data/input_8192.in
	./rmm data/input_16384.in

runn: ../datacommon/input_16.in ../datacommon/input_4096.in ../datacommon/input_8192.in ../datacommon/input_16384.in rmmm
	./rmmm ../datacommon/input_16.in
	./rmmm ../datacommon/input_4096.in
	./rmmm ../datacommon/input_8192.in
	./rmmm ../datacommon/input_16384.in

clean:
	rm rmm
	rm rmmm
