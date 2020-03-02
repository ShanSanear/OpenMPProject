#include <omp.h>
#include <cstdio>

using namespace std;

void for_loop_example() {
    int n = 1000;
    double a[1000];
    double b[1000];
    bool firstLoop = false;

#pragma omp parallel for private(firstLoop)
    for (int j = 0; j < n; j++) {
        if (!firstLoop) {
            firstLoop = true;
            printf("This is first run in this loop. Thread: %d Loop counter: %d\n", omp_get_thread_num(), j);
        }
        a[j] = 2 * j;
        b[j] = b[j] * 2;
    }
}

int main() {
    for_loop_example();
}