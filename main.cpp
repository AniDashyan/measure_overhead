#include <iostream>
#include <chrono>
#include <cstdlib>

void func(int x) {
    volatile int y = x + 1;
}

int main() {
    const int iters = 100'000'000; 

    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < iters; ++i) {
        func(i);
    }

    auto end1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    std::cout << "Function call time: " << duration1 << " ms\n";

    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < iters / 100; ++i) { // fewer to avoid huge allocations
        void* ptr = malloc(64);
        free(ptr);
    }
    auto end2 = std::chrono::steady_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    std::cout << "Malloc/Free time: " << duration2 << " ms\n";

    return 0;
}
