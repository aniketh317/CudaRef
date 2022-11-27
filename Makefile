all: datacommon/input_16.in datacommon/input_4096.in datacommon/input_8192.in datacommon/input_16384.in rmmcpu rmmcpu2 rmmgpu rmmgpu2

rmmcpu: PartA/main.cpp PartA/header/single_thread.h PartA/header/multi_thread.h
	g++ -g -ggdb PartA/main.cpp -o rmmcpu -I PartA/header -lpthread -mavx -mavx2

rmmcpu2: PartA/main2.cpp PartA/header/single_thread.h PartA/header/multi_thread.h
	g++ -g -ggdb PartA/main2.cpp -o rmmcpu2 -I PartA/header -lpthread -mavx -mavx2

rmmgpu: PartB/main.cu PartB/header/gpu_thread.h
	nvcc PartB/main.cu -o rmmgpu -I PartB/header

rmmgpu2: PartB/main2.cu PartB/header/gpu_thread.h
	nvcc PartB/main2.cu -o rmmgpu2 -I PartB/header

data/generate: data/generate.cpp
	g++ ./data/generate.cpp -o ./data/generate

datacommon/input_16.in: data/generate
	./data/generate 16 

datacommon/input_512.in: data/generate
	./data/generate 512 

datacommon/input_1024.in: data/generate
	./data/generate 1024 

datacommon/input_4096.in: data/generate
	./data/generate 4096 

datacommon/input_8192.in: data/generate
	./data/generate 8192 

datacommon/input_16384.in: data/generate
	./data/generate 16384 

runcpu: datacommon/input_16.in datacommon/input_4096.in datacommon/input_8192.in datacommon/input_16384.in rmmcpu
	./rmmcpu data/input_16.in
	./rmmcpu data/input_4096.in
	./rmmcpu data/input_8192.in
	./rmmcpu data/input_16384.in

runcpu2: datacommon/input_16.in datacommon/input_4096.in datacommon/input_8192.in datacommon/input_16384.in rmmcpu2
	./rmmcpu2 datacommon/input_16.in
	./rmmcpu2 datacommon/input_4096.in
	./rmmcpu2 datacommon/input_8192.in
	./rmmcpu2 datacommon/input_16384.in


rungpu: datacommon/input_16.in datacommon/input_4096.in datacommon/input_8192.in datacommon/input_16384.in rmmgpu
	./rmmgpu data/input_16.in
	./rmmgpu data/input_4096.in
	./rmmgpu data/input_8192.in
	./rmmgpu data/input_16384.in

runcpu2: datacommon/input_16.in datacommon/input_4096.in datacommon/input_8192.in datacommon/input_16384.in rmmgpu2
	./rmmgpu2 datacommon/input_16.in
	./rmmgpu2 datacommon/input_4096.in
	./rmmgpu2 datacommon/input_8192.in
	./rmmgpu2 datacommon/input_16384.in

clean:
	rm rmmcpu
	rm rmmcpu2