
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void evenOddSort(int* a, int size) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = 0; i < size; i += 2) {
        if (id + i < size - 1) {
            if (a[id + i] > a[id + i + 1]) {
                int temp = a[id + i];
                a[id + i] = a[id + i + 1];
                a[id + i + 1] = temp;
            }
        }
        __syncthreads();

        if (id + i + 1 < size - 1) {
            if (a[id + i + 1] > a[id + i + 2]) {
                int temp = a[id + i + 1];
                a[id + i + 1] = a[id + i + 2];
                a[id + i + 2] = temp;
            }
        }
        __syncthreads();
    }
}

__global__ void radixSort(int* a, int size, int bit) 
{
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;

    int sorted[];

    int count[sizeof(int) * 8] = { 0 };

    for (int i = idx; i < size; i += stride) 
    {
        ++count[(a[i] >> bit) & (sizeof(int) * 8 - 1)];
    }
    __syncthreads();

    for (int i = size - 1; i >= 0; i -= stride) 
    {
        sorted[count[(a[i] >> bit) & (sizeof(int) * 8 - 1)] - 1] = a[i];
        --count[(a[i] >> bit) & (sizeof(int) * 8 - 1)];
    }
    __syncthreads();

    for (int i = idx; i < size; i += stride) 
    {
        a[i] = sorted[i];
    }
}

void evenOdd(int* array, int size)
{
    int* a;

    cudaMalloc(&a, size * sizeof(int));
    cudaMemcpy(a, array, size * sizeof(int), cudaMemcpyHostToDevice);

    evenOddSort<<<2, size / 2>>> (a, size);

    cudaMemcpy(array, a, size * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(a);
}

void radix(int* array, int size)
{
    int* a;

    cudaMalloc(&a, size * sizeof(int));
    cudaMemcpy(a, array, size * sizeof(int), cudaMemcpyHostToDevice);

    for (int bit = 0; bit < sizeof(int) * 8; ++bit) {
        radixSort<<<sizeof(int) * 8, size>>> (a, size, bit);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(array, a, size * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(a);
}

int main() {
    // Nem biztos, hogy mukodik, mivel otthon megfelelo videokartya hianyaban nem tudtam kiprobalni

    const int size = 5;
    int array[size] = { 12, 5, 3, 4, 1};
    
    //evenOdd(array, size);
    //radix(array, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    
    return 0;
}
