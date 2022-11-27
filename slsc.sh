#!/bin/sh
#SBATCH --job-name=avss_cute16384 # Job name
#SBATCH --ntasks=1 # Run a single task
#SBATCH --cpus-per-task=18 #Use 18 cpus
#SBATCH --time=24:00:00 # Time limit hrs:min:sec
#SBATCH --output=avss_cute16384.out # Standard output and error log
#SBATCH --gres=gpu:2
#SBATCH --partition=med_24h_4gpu
pwd; hostname; date | tee result
nvidia-smi
./rmmgpu2 "datacommon/input_16384.in"