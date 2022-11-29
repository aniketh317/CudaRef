#!/bin/sh
#SBATCH --job-name=avss_multi8192 # Job name
#SBATCH --ntasks=1 # Run a single task
#SBATCH --cpus-per-task=18 #Use 18 cpus
#SBATCH --time=24:00:00 # Time limit hrs:min:sec
#SBATCH --output=avss_multi8192.out # Standard output and error log
#SBATCH --partition=med_24h_4gpu
pwd; hostname; date | tee result
nvidia-smi
./rmmcpu3 "datacommon/input_8192.in"