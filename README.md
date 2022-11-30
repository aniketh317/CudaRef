# Reducing Matrix Multiplication optimisation
Optimize reducing matrix multiplication using hardware counters.
Contained are two folders:
* PartA: Contains setup for single-threaded and multi-threaded program.
* PartB: Contains setup for GPU program.

There is a MakeFile at the root of the project.

# DATA
*Targets for generating data files(.ini files) for various dimensions are all present in the same Makefile
The data generated go into the datacommon(data common for Part-A, Part-B) folder.
For generating object file for datagenerate.cpp use
```
make data/generate
```
Then for generating a random n x n(n \in 16,1024,2048,4096,8192,16384) Data, which goes into datacommon folder do
```
make datacommon/input_{n}.in
```

## PARTA
Part-A folder has header files for Single and Multi Thread implementations
rmmcpu, rmmcpu2, rmmcpu3 are object file targets for main.cpp, main2, main3.cpp in Part-A folder. 
```
make rmmcpu
make rmmcpu2
make rmmcpu3
```
If compilation, data generation(if not present already) and running on sample inputs is required do
```
make runcpu
make runcpu2
make runcpu3
```
## PARTB
Part-B folder has header files for Gpu Thread implementations
rmmgpu, rmmgpu2 are object file targets for main.cu and main2.cu in Part-B. nvcc used for compilation of .cu files

```
make rmmgpu
make rmmgpu2
```
* If compilation, data generation(if not present already) and running on sample inputs is required do
```
make rungpu
make rungpu2
```
