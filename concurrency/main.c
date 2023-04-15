#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <threads.h>

#define NUM_THREADS 10
intmax_t result = 0;
const intmax_t N = 200000;
mtx_t lock;

bool is_prime(intmax_t num) {
    for (intmax_t i = 2; i <= (num / 2); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int count_prime(void* arg) {
    long int id = (long int)arg;
    for (intmax_t i = 2 + id; i < N; i += NUM_THREADS) {
        if (is_prime(i)) {
            mtx_lock(&lock);
            result++;
            mtx_unlock(&lock);
        }
    }
    return 0;
}

int main() {
    thrd_t handles[NUM_THREADS] = {0};
    mtx_init(&lock, mtx_plain);
    for (long int i = 0; i < NUM_THREADS; i++) {
        thrd_create(&handles[i], count_prime, (void*)i);
    }
    for (long int i = 0; i < NUM_THREADS; i++) {
        thrd_join(handles[i], NULL);
    }
    printf("number of primes of %ld is %ld\n", N, result);
    mtx_destroy(&lock);
}
