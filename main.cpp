#include <omp.h>
#include <cstdio>

using namespace std;
static double a[10000000];
static double b[10000000];
static double c[10000000];

void for_loop_example(int num_of_threads) {
    omp_set_num_threads(num_of_threads);
    printf("Running with %d threads.", num_of_threads);
    long n = 10000000;
    long double array_sum = 0;
    bool first_loop = false;
    double start_time = omp_get_wtime();
#pragma omp parallel for private(first_loop)
    for (int j = 0; j < n; j++) {
        if (!first_loop) {
            first_loop = true;
            //printf("This is first run in this loop. Thread: %d Loop counter: %d\n", omp_get_thread_num(), j);
        }
        a[j] = 2 * j;
        b[j] = b[j] * 2;
        array_sum += b[j] + a[j];
    }
    double elapsed_time = omp_get_wtime() - start_time;
//    printf("Output value of the array is: %f\n", array_sum);
    printf("Elapsed time: %f\n", elapsed_time);
}

int main() {
    for_loop_example(4);
    for_loop_example(8);
    for_loop_example(10);
    for_loop_example(20);
    for_loop_example(40);
    for_loop_example(80);
}
