
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// the predicate here is divisibility by 3
__global__ void mapPredicate(int* in, int* out, unsigned int dataSize)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	if (id > dataSize) return;

	out[id] = 0;
	if (in[id] % 3 == 0) {
		out[id] = 1;
	}
}

__global__ void scan(int* in, int* out, unsigned int dataSize)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	if (id > dataSize) return;
	out[id] = in[id];

	__syncthreads();
	for (int d = 1, d_pow = 1; d < (log2f(dataSize) + 1); d++) {
		if (id + 1 > d_pow) {
			out[id] += out[id - d_pow];
		}
		d_pow *= 2;
		__syncthreads();
	}
}

__global__ void compact(int* in, int* predicates, int* offsets, int* out, unsigned int dataSize)
{
	int id = threadIdx.x + blockIdx.x * blockDim.x;
	if (id > dataSize) return;

	if (predicates[id] == 1) {
		out[offsets[id] - 1] = in[id];
	}
}

cudaError_t withCuda(int* compacted, const int* numbers, unsigned int size)
{
	int* dev_numbers = 0;
	int* dev_predicates = 0;
	int* dev_offsets = 0;
	int* dev_compacted = 0;
	cudaError_t cudaStatus;

	// Choose which GPU to run on, change this on a multi-GPU system
	cudaStatus = cudaSetDevice(0);

	// Allocate GPU buffers for three vectors (two input, one output
	cudaStatus = cudaMalloc((void**)&dev_compacted, size * sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_numbers, size * sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_predicates, size * sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_offsets, size * sizeof(int));

	// Copy input vectors from host memory to GPU buffers.
	cudaStatus = cudaMemcpy(dev_numbers, numbers, size * sizeof(int), cudaMemcpyHostToDevice);
	mapPredicate << <1, size >> > (dev_numbers, dev_predicates, size);
	scan << <1, size >> > (dev_predicates, dev_offsets, size);
	compact << <1, size >> > (dev_numbers, dev_predicates, dev_offsets, dev_compacted, size);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(compacted, dev_compacted, size * sizeof(int), cudaMemcpyDeviceToHost);

	cudaFree(dev_numbers);
	cudaFree(dev_predicates);
	cudaFree(dev_offsets);
	cudaFree(dev_compacted);

	return cudaStatus;
}

int main()
{
	const int arraySize = 1024;
	int* numbers = (int*)malloc(arraySize * sizeof(int));
	int* compacted = (int*)malloc(arraySize * sizeof(int));

	for (int i = 0; i < arraySize; i++) {
		numbers[i] = i + 1;
	}


	cudaError_t cudaStatus = withCuda(compacted, numbers, arraySize);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "withCuda failed!");
		return 1;
	}

	const int max = fmin(1000, arraySize);

	printf("numbers:   ");
	for (int i = 0; i < max - 1; i++) {
		printf("%4d, ", numbers[i]);
	}
	printf("%4d ", numbers[max - 1]);

	printf("\ncompacted: ");
	for (int i = 0; i < max - 1; i++) {
		printf("%4d, ", compacted[i]);
	}
	printf("%4d ", compacted[max - 1]);


	// cudaDeviceReset must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceReset failed!");
		return 1;
	}

	free(numbers);
	free(compacted);

	return 0;
}
