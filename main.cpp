#include <omp.h>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;
static double a[10000000];
static double b[10000000];

void single_threaded_loop(bool should_sum_all) {
    printf("Running single threaded for loop\n");
    long n = 10000000;
    long double array_sum = 0;
    bool first_loop = false;
    double start_time = omp_get_wtime();
    for (int j = 0; j < n; j++) {
        if (!first_loop) {
            first_loop = true;
            //printf("This is first run in this loop. Thread: %d Loop counter: %d\n", omp_get_thread_num(), j);
        }
        a[j] = 2 * j;
        b[j] = b[j] * 2;
        if (should_sum_all) {
            array_sum += b[j] + a[j];
        }
    }
    for (int i = 0; i < 32; i++) {
        printf("ordered_pragma index %d from thread %d\n", i, 0);
    }
    double elapsed_time = omp_get_wtime() - start_time;
    if (should_sum_all) {
        printf("Output value of the array is: %Le\n", array_sum);
    }
    printf("Elapsed time: %f\n\n", elapsed_time);
}

void for_loop_example(int num_of_threads, bool should_sum_all) {
    omp_set_num_threads(num_of_threads);
    printf("Running with %d threads.\n", num_of_threads);
    long n = 10000000;
    long double array_sum = 0;
    bool first_loop = false;
    double start_time = omp_get_wtime();
#pragma omp parallel for private(first_loop) default(none) shared(a, b, n, array_sum, should_sum_all)
    for (int j = 0; j < n; j++) {
        if (!first_loop) {
            first_loop = true;
            //printf("This is first run in this loop. Thread: %d Loop counter: %d\n", omp_get_thread_num(), j);
        }
        a[j] = 2 * j;
        b[j] = b[j] * 2;
        if (should_sum_all) {
#pragma omp critical
            {
                array_sum += b[j] + a[j];
            }
        }

    }
#pragma omp parallel for ordered default(none)
    for (int i = 0; i < 32; i++) {
        printf("ordered_pragma index %d from thread %d\n", i, omp_get_thread_num());
    }
    double elapsed_time = omp_get_wtime() - start_time;
    if (should_sum_all) {
        printf("Output value of the array is: %Le\n", array_sum);
    }
    printf("Elapsed time: %f\n\n", elapsed_time);
}

void run_example_functions(bool should_sum_all) {
    single_threaded_loop(should_sum_all);
    for_loop_example(2, should_sum_all);
    for_loop_example(4, should_sum_all);
    for_loop_example(8, should_sum_all);
}

int main() {
    printf("Running functions without need to access shared resource\n");
    run_example_functions(false);
    printf("Running functions with shared access to the resource\n");
    run_example_functions(true);

}
