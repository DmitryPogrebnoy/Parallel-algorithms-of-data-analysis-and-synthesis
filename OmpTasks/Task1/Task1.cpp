#include <iostream>
#include <omp.h>

using namespace std;

long const N_TEST = 100000000;

double max(int A[], int i, int j, int threadNumber)
{
    double t1 = omp_get_wtime();
    int max_val = A[0];

    #pragma omp parallel for reduction(max:max_val) num_threads(threadNumber)
    for (int idx = i; idx < j; idx++)
        max_val = max_val > A[idx] ? max_val : A[idx];

    if (j != N_TEST) {
        cout << "Max value is " << max_val << endl;
    }
    return omp_get_wtime() - t1;
}

int main(int argc, char* argv[])
{
    cout.precision(10);
    int B[10] = { 1,2,3,4,5,6,7,8,9,10 };
    cout << "Test array is { 1,2,3,4,5,6,7,8,9,10 }" << endl;
    cout << "Test run for array with 10 elements - " << max(B, 0, 10, 12) << endl << endl;

    int N;
    if (argc == 2) {
        N = atoi(argv[1]);
    } else {
        N = N_TEST;
    }
   
    for (int i = 1; i < 11; i++) {
        int* A = new int[N];
        for (int i = 0; i < N; i++) {
            A[i] = rand();
        }
        int K = 20;
        double time = 0;
        for (int j = 0; j < K; j++) {
            time += max(A, 0, N, i);
        }
        cout.precision(10);
        cout << "Run with " << i << " threads takes average time - " << time/K << endl << endl;
        delete[] A;
    }
}